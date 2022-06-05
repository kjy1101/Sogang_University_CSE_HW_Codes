#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

extern "C"
{
	int hybrd1_(void fcn(int*, double*, double*, int*), int*, double*, double*, double*, int*, double*, int*);
}

void fcn3_5(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = 10 * x[0] - 2 * x[1] * x[1] + x[1] - 2 * x[2] - 5;
	fvec[1] = 8 * x[1] * x[1] + 4 * x[2] * x[2] - 9;
	fvec[2] = 8 * x[1] * x[2] + 4;
	/********************************/
}

void practice3_5(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 1.0, -1.0, 1.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-5.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/
	printf("�ʱⰪ1: %.2lf %.2lf %.2lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "�ʱⰪ1: %.2lf %.2lf %.2lf\n", x[0], x[1], x[2]);
	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf %lf\n", info, x[0], x[1], x[2]);
	printf("f1=%lf, f2=%lf, f3=%lf\n\n", fvec[0], fvec[1], fvec[2]);
	fprintf(fp_w, "%d %lf %lf %lf\n", info, x[0], x[1], x[2]);
	fprintf(fp_w, "f1=%lf, f2=%lf, f3=%lf\n\n", fvec[0], fvec[1], fvec[2]);

	x[0] = 1.0; x[1] = 1.0; x[2] = -1.0;
	printf("�ʱⰪ2: %.2lf %.2lf %.2lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "�ʱⰪ2: %.2lf %.2lf %.2lf\n", x[0], x[1], x[2]);
	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf %lf\n", info, x[0], x[1], x[2]);
	printf("f1=%lf, f2=%lf, f3=%lf\n\n", fvec[0], fvec[1], fvec[2]);
	fprintf(fp_w, "%d %lf %lf %lf\n", info, x[0], x[1], x[2]);
	fprintf(fp_w, "f1=%lf, f2=%lf, f3=%lf\n\n", fvec[0], fvec[1], fvec[2]);
	/********************************/

	fclose(fp_w);
}