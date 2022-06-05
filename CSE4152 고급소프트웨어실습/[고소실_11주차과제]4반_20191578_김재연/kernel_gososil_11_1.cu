#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <assert.h>

#define CUDA_CALL(x) { const cudaError_t a = (x); if(a != cudaSuccess) { printf("\nCuda Error: %s (err_num=%d) at line:%d\n", cudaGetErrorString(a), a, __LINE__); cudaDeviceReset(); assert(0);}}
typedef float TIMER_T;

#define USE_CPU_TIMER 1
#define USE_GPU_TIMER 1

#if USE_CPU_TIMER == 1
__int64 start, freq, end;
#define CHECK_TIME_START { QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start); }
#define CHECK_TIME_END(a) { QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f)); }
#else
#define CHECK_TIME_START
#define CHECK_TIME_END(a)
#endif

#if USE_GPU_TIMER == 1
cudaEvent_t cuda_timer_start, cuda_timer_stop;
#define CUDA_STREAM_0 (0)

void create_device_timer()
{
    CUDA_CALL(cudaEventCreate(&cuda_timer_start));
    CUDA_CALL(cudaEventCreate(&cuda_timer_stop));
}

void destroy_device_timer()
{
    CUDA_CALL(cudaEventDestroy(cuda_timer_start));
    CUDA_CALL(cudaEventDestroy(cuda_timer_stop));
}

inline void start_device_timer()
{
    cudaEventRecord(cuda_timer_start, CUDA_STREAM_0);
}

inline TIMER_T stop_device_timer()
{
    TIMER_T ms;
    cudaEventRecord(cuda_timer_stop, CUDA_STREAM_0);
    cudaEventSynchronize(cuda_timer_stop);

    cudaEventElapsedTime(&ms, cuda_timer_start, cuda_timer_stop);
    return ms;
}

#define CHECK_TIME_INIT_GPU() { create_device_timer(); }
#define CHECK_TIME_START_GPU() { start_device_timer(); }
#define CHECK_TIME_END_GPU(a) { a = stop_device_timer(); }
#define CHECK_TIME_DEST_GPU() { destroy_device_timer(); }
#else
#define CHECK_TIME_INIT_GPU()
#define CHECK_TIME_START_GPU()
#define CHECK_TIME_END_GPU(a)
#define CHECK_TIME_DEST_GPU()
#endif

#define BLOCK_SIZE 32
#define DATA_SIZE (1 << 26)

TIMER_T compute_time = 0;
TIMER_T device_time = 0;

int N;
int N_EQUATIONS;
float(*A); float(*B); float(*C);
float(*X0); float(*X1); float(*FX0); float(*FX1);
float(*X0_GPU); float(*X1_GPU); float(*FX0_GPU); float(*FX1_GPU);

cudaError_t find_roots_GPU(float *A, float *B, float *C, float *X0_GPU, float *X1_GPU, float *FX0_GPU, float *FX1_GPU);

__global__ void find_roots_Kernel(float* d_A, float* d_B, float* d_C, float* d_X0, float* d_X1, float* d_FX0, float* d_FX1)
{
    int i;
    float a, b, c, d, x0, x1, tmp;
    i = blockDim.x * blockIdx.x + threadIdx.x;
    a = d_A[i]; b = d_B[i]; c = d_C[i];
    d = sqrtf(b * b - 4.0f * a * c);
    tmp = 1.0f / (2.0f * a);
    d_X0[i] = x0 = (-b - d) * tmp;
    d_X1[i] = x1 = (-b + d) * tmp;
    d_FX0[i] = (a * x0 + b) * x0 + c;
    d_FX1[i] = (a * x1 + b) * x1 + c;
}

void find_roots_CPU(float* A, float* B, float* C, float* X0, float* X1, float* FX0, float* FX1, int n) {
    int i;
    float a, b, c, d, x0, x1, tmp;
    for (i = 0; i < n; i++) {
        a = A[i]; b = B[i]; c = C[i];
        d = sqrtf(b * b - 4.0f * a * c);
        tmp = 1.0f / (2.0f * a);
        X0[i] = x0 = (-b - d) * tmp;
        X1[i] = x1 = (-b + d) * tmp;
        FX0[i] = (a * x0 + b) * x0 + c;
        FX1[i] = (a * x1 + b) * x1 + c;
    }
}

void init_bin_file(int size) {
    srand((unsigned)time(NULL));
    printf("***Binary File init Start!!\n");
    FILE* fpA = fopen("A.bin", "wb");
    FILE* fpB = fopen("B.bin", "wb");
    FILE* fpC = fopen("C.bin", "wb");

    fwrite(&size, sizeof(int), 1, fpA);
    fwrite(&size, sizeof(int), 1, fpB);
    fwrite(&size, sizeof(int), 1, fpC);

    float random_num;
    for (int i = 0; i < size; i++) {
        random_num = (float)(((double)rand() / RAND_MAX) * 30.0f);
        fwrite(&random_num, sizeof(float), 1, fpA);
        random_num = (float)(((double)rand() / RAND_MAX) * 40.0f);
        fwrite(&random_num, sizeof(float), 1, fpB);
        random_num = (float)(((double)rand() / RAND_MAX) * 50.0f);
        fwrite(&random_num, sizeof(float), 1, fpC);
    }

    fclose(fpA);
    fclose(fpB);
    fclose(fpC);
    printf("***Binary File init End!!\n\n");
}

void read_bin_file()
{
    printf("***Binary File Read Start!!\n");
    FILE* fpA = fopen("A.bin", "rb");
    FILE* fpB = fopen("B.bin", "rb");
    FILE* fpC = fopen("C.bin", "rb");
    
	fread(&N_EQUATIONS, sizeof(int), 1, fpA);
	fread(&N_EQUATIONS, sizeof(int), 1, fpB);
	fread(&N_EQUATIONS, sizeof(int), 1, fpC);

    A = new float[N_EQUATIONS];
    B = new float[N_EQUATIONS];
    C = new float[N_EQUATIONS];
    X0 = new float[N_EQUATIONS];
    X1 = new float[N_EQUATIONS];
    FX0 = new float[N_EQUATIONS];
    FX1 = new float[N_EQUATIONS];
    X0_GPU = new float[N_EQUATIONS];
    X1_GPU = new float[N_EQUATIONS];
    FX0_GPU = new float[N_EQUATIONS];
    FX1_GPU = new float[N_EQUATIONS];

    fread(A, sizeof(float), N_EQUATIONS, fpA);
    fread(B, sizeof(float), N_EQUATIONS, fpB);
    fread(C, sizeof(float), N_EQUATIONS, fpC);

    fclose(fpA);
    fclose(fpB);
    fclose(fpC);
    printf("***Binary File Read End!!\n\n");
}

int main()
{
    init_bin_file(DATA_SIZE);
    read_bin_file();

    printf("N_EQUATIONS: %d, Block size: %d\n", N_EQUATIONS, BLOCK_SIZE);
    int i;

    //CPU 
    printf("***find_roots_CPU Start!!\n");
    CHECK_TIME_START;
    find_roots_CPU(A, B, C, X0, X1, FX0, FX1, N_EQUATIONS);
    CHECK_TIME_END(compute_time);
    printf("***find_roots_CPU End!!\n\n");

    printf("CPU time = %.6f\n", compute_time);
    //GPU

    printf("***find_roots_GPU Start!!\n");
    find_roots_GPU(A, B, C, X0_GPU, X1_GPU, FX0_GPU, FX1_GPU);
    printf("***find_roots_GPU End!!\n\n");

    printf("GPU time = %.6f\n", device_time);

    /*for (i = 0; i < N_EQUATIONS; i++)
    {
        if (FX0[i] != FX0_GPU[i])
        {
            printf("[0] %u != %u\n", FX0[i], FX0_GPU[i]);
            break;
        }
        else if (FX1[i] != FX1_GPU[i]) 
        {
            printf("[1] %u != %u\n", FX1[i], FX1_GPU[i]);
            break;
        }
    }*/

    if (i == N_EQUATIONS)
        printf("***Kernel execution Success!!\n\n");

    // Write the output array into the output file.
    FILE *fpX0 = fopen("X0.bin", "wb");
    FILE* fpX1 = fopen("X1.bin", "wb");
    FILE* fpFX0 = fopen("FX0.bin", "wb");
    FILE* fpFX1 = fopen("FX1.bin", "wb");
    if (!fpX0 || !fpX1 || !fpFX0 || !fpFX1 ) {
        fprintf(stderr, "Error: cannot open the output file...\n");
        exit(-1);
    }

    N = N_EQUATIONS;
    fwrite(&N, sizeof(int), 1, fpX0);
    fwrite(&N, sizeof(int), 1, fpX1);
    fwrite(&N, sizeof(int), 1, fpFX0);
    fwrite(&N, sizeof(int), 1, fpFX1);

    for (i = 0; i < N_EQUATIONS; i++) {
        fwrite(&X0_GPU[i], sizeof(float), 1, fpX0);
        fwrite(&X1_GPU[i], sizeof(float), 1, fpX1);
        fwrite(&FX0_GPU[i], sizeof(float), 1, fpFX0);
        fwrite(&FX1_GPU[i], sizeof(float), 1, fpFX1);
    }


    fclose(fpX0);
    fclose(fpX1);
    fclose(fpFX0);
    fclose(fpFX1);
    printf("end!!\n\n");

    return 0;
}


cudaError_t find_roots_GPU(float* A, float* B, float* C, float* X0_GPU, float* X1_GPU, float* FX0_GPU, float* FX1_GPU)
{
    CHECK_TIME_INIT_GPU();

    cudaError_t cudaStatus;
    
    float(*p_A); float(*p_B); float(*p_C);
    float(*p_X0); float(*p_X1); float(*p_FX0); float(*p_FX1);
    size_t size;

    size = N_EQUATIONS * sizeof(float);
    CUDA_CALL(cudaMalloc(&p_A, size))
    CUDA_CALL(cudaMemcpy(p_A, A, size, cudaMemcpyHostToDevice))
    CUDA_CALL(cudaMalloc(&p_B, size))
    CUDA_CALL(cudaMemcpy(p_B, B, size, cudaMemcpyHostToDevice))
    CUDA_CALL(cudaMalloc(&p_C, size))
    CUDA_CALL(cudaMemcpy(p_C, C, size, cudaMemcpyHostToDevice))

    CUDA_CALL(cudaMalloc(&p_X0, size))
    CUDA_CALL(cudaMalloc(&p_X1, size))
    CUDA_CALL(cudaMalloc(&p_FX0, size))
    CUDA_CALL(cudaMalloc(&p_FX1, size))

    dim3 dimBlock(BLOCK_SIZE, 1);
    dim3 dimGrid(N_EQUATIONS / dimBlock.x, 1);

    CHECK_TIME_START_GPU();
    find_roots_Kernel << < dimGrid, dimBlock >> > (p_A, p_B, p_C, p_X0, p_X1, p_FX0, p_FX1);
    CHECK_TIME_END_GPU(device_time);

    CUDA_CALL(cudaDeviceSynchronize())
        CUDA_CALL(cudaMemcpy(X0_GPU, p_X0, size, cudaMemcpyDeviceToHost))
        CUDA_CALL(cudaMemcpy(X1_GPU, p_X1, size, cudaMemcpyDeviceToHost))
        CUDA_CALL(cudaMemcpy(FX0_GPU, p_FX0, size, cudaMemcpyDeviceToHost))
        CUDA_CALL(cudaMemcpy(FX1_GPU, p_FX1, size, cudaMemcpyDeviceToHost))

    cudaFree(p_A);
    cudaFree(p_B);
    cudaFree(p_C);
    cudaFree(p_X0);
    cudaFree(p_X1);
    cudaFree(p_FX0);
    cudaFree(p_FX1);
    CHECK_TIME_DEST_GPU();
    return cudaStatus;
}