#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>

#include <math.h>
#include <time.h>
#include <Windows.h>

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;
float compute_time1, compute_time2;


#define MATDIM 1024
#define HW1_N 100000
float *hw1_x, hw1_E, hw1_var1, hw1_var2;
float hw2_a, hw2_b, hw2_c, hw2_naive_ans[2], hw2_pre_ans[2];

/* hw1 */
void init_hw1(int fixed);
void hw1_calc_e();
void hw1_calc_var1();
void hw1_calc_var2();
/* hw2 */
void hw2_naive();
void hw2_safe();
float hw2_verify(float x);
/* hw3 */
#define HW3_N 100000

void main(void)
{
	srand((unsigned)time(NULL));

	/* hw1 */
	puts("====== hw1 ======");
	init_hw1(1);
	hw1_calc_e();
	CHECK_TIME_START;
	hw1_calc_var1();
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw1_calc_var1 = %f ms\n", compute_time);
	printf("hw1_calc_var1 value = %.15f\n", hw1_var1);


	CHECK_TIME_START;
	hw1_calc_var2();
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw1_calc_var2 = %f ms\n", compute_time);
	printf("hw1_calc_var2 value = %.15f\n", hw1_var2);
	puts("");
	
	/* hw2 */
	puts("====== hw2 ======");
	printf("a, b, c : ");
	scanf("%f %f %f", &hw2_a, &hw2_b, &hw2_c);
	hw2_naive();
	hw2_safe();
	printf("naive result    : %.15f, %.15f\n", hw2_naive_ans[0], hw2_naive_ans[1]);
	printf("advanced result : %.15f, %.15f\n", hw2_pre_ans[0], hw2_pre_ans[1]);
	puts("");
	printf("Verifying naive ans    : %.15f, %.15f\n", hw2_verify(hw2_naive_ans[0]), hw2_verify(hw2_naive_ans[1]));
	printf("Verifying advanced ans : %.15f, %.15f\n", hw2_verify(hw2_pre_ans[0]), hw2_verify(hw2_pre_ans[1]));
	puts("");


	/* hw3 */
	puts("====== hw3 ======");
	int i = 0, j = 0;
	float a[HW3_N], b[HW3_N];
	
	/* Loop Interchange */
	float a2[100][200];
	CHECK_TIME_START;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 200; j++) {
			a2[i][j] = (float)(i + j);
		}
	}
	CHECK_TIME_END(compute_time);
	printf("[1] The runtime without loop interchange : %.3f ms\n", compute_time * 1000);
	printf("[1] a2[99][199] = %f\n", a2[99][199]);

	CHECK_TIME_START;
	for (j = 0; j < 200; j++) {
		for (i = 0; i < 100; i++) {
			a2[i][j] = (float)(i + j);
		}
	}
	CHECK_TIME_END(compute_time);
	printf("[1] The runtime with loop interchange : %.3f ms\n", compute_time * 1000);
	printf("[1] a2[99][199] = %f\n\n", a2[99][199]);



	/* Loop Inversion */
	i = 0;
	CHECK_TIME_START;
	while (i < HW3_N) {
		a[i] = i;
		i++;
	}
	CHECK_TIME_END(compute_time);
	printf("[2] The runtime without loop inversion : %.3f ms\n", compute_time * 1000);
	printf("[2] a[%d] = %f\n", HW3_N - 1, a[HW3_N - 1]);

	i = 0;
	CHECK_TIME_START;
	if (i < HW3_N) {
		do {
			a[i] = i;
			i++;
		} while (i < HW3_N);
	}
	CHECK_TIME_END(compute_time);
	printf("[2] The runtime with loop inversion : %.3f ms\n", compute_time * 1000);
	printf("[2] a[%d] = %f\n\n", HW3_N - 1, a[HW3_N - 1]);



	/* Loop Unswitching */
	int w = 1;
	a[0] = 0.0;
	CHECK_TIME_START;
	for (i = 0; i < HW3_N; i++) {
		if (w) b[i] = (float)i;
		a[i] = b[i];
	}
	CHECK_TIME_END(compute_time);
	printf("[3] The runtime without loop unswitching : %.3f ms\n", compute_time * 1000);
	printf("[3] a[%d] = %f, b[%d] = %f\n", HW3_N - 1, a[HW3_N - 1], HW3_N - 1, b[HW3_N - 1]);

	CHECK_TIME_START;
	if (w) {
		for (i = 0; i < HW3_N; i++) {
			b[i] = (float)i;
			a[i] = b[i];
		}
	}
	else {
		for (i = 0; i < HW3_N; i++) {
			a[i] += b[i];
		}
	}
	CHECK_TIME_END(compute_time);
	printf("[3] The runtime with loop unswitching : %.3f ms\n", compute_time * 1000);
	printf("[3] a[%d] = %f, b[%d] = %f\n\n", HW3_N - 1, a[HW3_N - 1], HW3_N - 1, b[HW3_N - 1]);



	/* Loop invariant code motion */
	i = 0;
	float x = 1.0, y = 2.0, z = 3.0;
	CHECK_TIME_START;
	while (i < HW3_N) {
		x = y + z;
		a[i] = (float)(6 * i + x * x);
		++i;
	}
	CHECK_TIME_END(compute_time);
	printf("[4] The runtime without loop invariant code motion : %.3f ms\n", compute_time * 1000);
	printf("[4] a[%d] = %f\n", HW3_N - 1, a[HW3_N - 1]);

	i = 0;
	CHECK_TIME_START;
	if (i < HW3_N) {
		x = y + z;
		float const t1 = x * x;
		do {
			a[i] = (float)(6 * i + t1);
			++i;
		} while (i < HW3_N);
	}
	CHECK_TIME_END(compute_time);
	printf("[4] The runtime with loop invariant code motion : %.3f ms\n", compute_time * 1000);
	printf("[4] a[%d] = %f\n\n", HW3_N - 1, a[HW3_N - 1]);



	/* Loop Peeling */
	int p = HW3_N - 1;
	CHECK_TIME_START;
	for (i = 0; i < HW3_N - 1; ++i) {
		b[i] = a[i] + a[p];
		p = i;
	}
	CHECK_TIME_END(compute_time);
	printf("[5] The runtime without loop peeling : %.3f ms\n", compute_time * 1000);
	printf("[5] b[%d] = %f\n", HW3_N - 2, b[HW3_N - 2]);

	CHECK_TIME_START;
	b[0] = a[0] + a[HW3_N - 1];
	for (i = 1; i < HW3_N - 1; ++i) {
		b[i] = a[i] + a[i - 1];
	}
	CHECK_TIME_END(compute_time);
	printf("[5] The runtime without loop peeling : %.3f ms\n", compute_time * 1000);
	printf("[5] b[%d] = %f\n\n", HW3_N - 2, b[HW3_N - 2]);
}

void init_hw1(int fixed)
{
	float *ptr;
	hw1_x = (float *)malloc(sizeof(float)*HW1_N);

	if (fixed)
	{
		float tmp = HW1_N;
		for (int i = 0; i < HW1_N; i++)
		{
			if( i & 1) tmp -= 0.0001;
			hw1_x[i] = tmp;
		}
	}
	else
	{
		srand((unsigned)time(NULL));
		ptr = hw1_x;
		for (int i = 0; i < HW1_N; i++)
			*ptr++ = ((float)rand() / (float)RAND_MAX) * 2;
	}
}
void hw1_calc_e()
{
	hw1_E = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_E += hw1_x[i];
	}
	hw1_E /= HW1_N;
}
void hw1_calc_var1()
{
	double temp1 = 0, temp2 = 0;
	for (int i = 0; i < HW1_N; i++) {
		temp1 += pow(hw1_x[i], 2);
		temp2 += hw1_x[i];
	}
	hw1_var1 = (HW1_N * temp1 - temp2 * temp2) / (HW1_N * (HW1_N - 1));
	hw1_var1 = sqrt(hw1_var1);
}
void hw1_calc_var2()
{
	hw1_var2 = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_var2 += pow(hw1_x[i] - hw1_E, 2);
	}
	hw1_var2 /= (HW1_N - 1);
	hw1_var2 = sqrt(hw1_var2);
}


/* hw2 */
void hw2_naive()
{
	hw2_naive_ans[0] = (-1 * hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
	hw2_naive_ans[1] = (-1 * hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
}
void hw2_safe()
{
	if (hw2_b > 0) {
		hw2_pre_ans[0] = (-2 * hw2_c) / (hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
		hw2_pre_ans[1] = (-1 * hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
	}
	else {
		hw2_pre_ans[0] = (-1 * hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c)) / (2 * hw2_a);
		hw2_pre_ans[1] = (-2 * hw2_c) / (hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
	}
}
float hw2_verify(float x)
{
	return hw2_a * x * x + hw2_b*x + hw2_c;
}