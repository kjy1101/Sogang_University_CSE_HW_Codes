#include "my_solver.h"

#define index_2d(row, col, dim) row*dim+col

extern "C"
{
	int gespp_(int*, float*, int*, int*, float*);
	int solve_(int*, float*, int*, int*, float*, float*);
};

void program3_4() {

	FILE* fp_r = fopen("linear_system_3-4.txt", "r");
	if (fp_r == NULL) {
		printf("%s file open error...\n", "linear_system_3-4.txt");
		return;
	}

	FILE* fp_w = fopen("solution_3-4.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "solution_3-4.txt");
		return;
	}

	int i, ia, j, n, *l;
	float* a, * x, * b, * s, * u, * aa, * bb;
	
	fscanf(fp_r, "%d", &n);
	a = (float*)malloc(sizeof(float) * (n * n));
	aa = (float*)malloc(sizeof(float) * (n * n));
	x = (float*)malloc(sizeof(float) * n);
	b = (float*)malloc(sizeof(float) * n);
	bb = (float*)malloc(sizeof(float) * n);
	s = (float*)malloc(sizeof(float) * n);
	u = (float*)malloc(sizeof(float) * n);
	l = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n * n; i++) {
		fscanf(fp_r, "%f", &a[i]);
		aa[i] = a[i];
	}
	for (i = 0; i < n; i++) {
		fscanf(fp_r, "%f", &b[i]);
		bb[i] = b[i];
	}
	ia = n;


	gespp_(&n, a, &ia, l, s);
	solve_(&n, a, &ia, l, b, x);


	float diff;
	float diff_u = 0;
	float diff_b = 0;

	for (i = 0; i < n; i++) {
		u[i] = 0;
		for (j = 0; j < n; j++) {
			u[i] += aa[index_2d(j, i, n)] * x[j];
		}
		u[i] -= bb[i];
	}

	for (i = 0; i < n; i++) {
		diff_u += u[i] * u[i];
		diff_b += bb[i] * bb[i];
	}
	diff_u = sqrt(diff_u);
	diff_b = sqrt(diff_b);
	diff = diff_u / diff_b;

	fprintf(fp_w, "%d\n", n);
	for (i = 0; i < n; i++) {
		printf("x[%d] = %f, ", i, x[i]);
		fprintf(fp_w, "%.6f\n", x[i]);
	}
	printf("\n오차: %.6f\n", diff);
	fprintf(fp_w, "오차: %.6f\n", diff);

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}