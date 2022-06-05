#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

extern "C"
{
	int hybrd1_(void fcn(int*, double*, double*, int*), int*, double*, double*, double*, int*, double*, int*);
}

void fcn3_2(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = x[0] + 10 * x[1] + 9;
	fvec[1] = sqrt(5) * (x[2] - x[3]) - 2 * sqrt(5);
	fvec[2] = pow(x[1] - 2 * x[2], 2) - 9;
	fvec[3] = sqrt(10) * pow(x[0] - x[3], 2) - 2 * sqrt(10);
	/********************************/
}

void program3_2(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.9, -0.9, 1.25, -1.25 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-2.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_found_3-2.txt");
		return;
	}

	printf("초기값: %.2lf %.2lf %.2lf %.2lf\n", x[0], x[1], x[2], x[3]);
	fprintf(fp_w, "초기값: %.2lf %.2lf %.2lf %.2lf\n", x[0], x[1], x[2], x[3]);

	hybrd1_(fcn3_2, &n, x, fvec, &tol, &info, wa, &lwa);

	printf("%d %lf %lf %lf %lf\n", info, x[0], x[1], x[2], x[3]);
	printf("f1=%lf, f2=%lf, f3=%lf, f4=%lf\n\n", fvec[0], fvec[1], fvec[2], fvec[3]);

	fprintf(fp_w, "%d %lf %lf %lf %lf\n", info, x[0], x[1], x[2], x[3]);
	fprintf(fp_w, "f1=%lf, f2=%lf, f3=%lf, f4=%lf\n\n", fvec[0], fvec[1], fvec[2], fvec[3]);
}