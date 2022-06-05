#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

extern "C"
{
	int hybrd1_(void fcn(int*, double*, double*, int*), int*, double*, double*, double*, int*, double*, int*);
}

void fcn3_7(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = 2 * x[0] * x[0] * x[0] - 12 * x[0] - x[1] - 1;
	fvec[1] = 3 * x[1] * x[1] - 6 * x[1] - x[0] - 3;
	/********************************/
}

void practice3_7(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-7.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-7.txt");
		return;
	}

	/********************************/
	x[0] = -3.0; x[1] = -2.5;
	printf("초기값1: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값1: %.2lf %.2lf\n", x[0], x[1]);
	hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf\n", info, x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%d %lf %lf\n", info, x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = -2.4; x[1] = 2.0;
	printf("초기값2: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값2: %.2lf %.2lf\n", x[0], x[1]);
	hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf\n", info, x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%d %lf %lf\n", info, x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = -1.0; x[1] = 2.0;
	printf("초기값3: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값3: %.2lf %.2lf\n", x[0], x[1]);
	hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf\n", info, x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%d %lf %lf\n", info, x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = -1.0; x[1] = -1.0;
	printf("초기값4: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값4: %.2lf %.2lf\n", x[0], x[1]);
	hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf\n", info, x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%d %lf %lf\n", info, x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = 2.0; x[1] = -1.0;
	printf("초기값5: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값5: %.2lf %.2lf\n", x[0], x[1]);
	hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf\n", info, x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%d %lf %lf\n", info, x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = 2.0; x[1] = 3.0;
	printf("초기값6: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값6: %.2lf %.2lf\n", x[0], x[1]);
	hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("%d %lf %lf\n", info, x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%d %lf %lf\n", info, x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	/********************************/

	fclose(fp_w);
}