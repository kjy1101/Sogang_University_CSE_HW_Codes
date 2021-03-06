#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

extern "C"
{
	int hybrj1_(void fcn(int*, double*, double*, double*, int*, int*), int*, double*, double*, double*, int*, double*, int*, double*, int*);
}

void fcn3_6(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag) {
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = 3 * x[0] * x[0] - 2 * x[1] * x[1] - 1;
		fvec[1] = x[0] * x[0] - 2 * x[0] + x[1] * x[1] + 2 * x[1] - 8;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 6 * x[0];				fjac[2] = -4 * x[1];
		fjac[1] = 2.0 * x[0] - 2;		fjac[3] = 2 * x[1] + 2;
		/********************************/
	}
}

void practice3_6(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-6.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-6.txt");
		return;
	}

	/********************************/
	x[0] = -2.0; x[1] = -1.5;
	printf("초기값1: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값1: %.2lf %.2lf\n", x[0], x[1]);
	hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	printf("%lf %lf\n", x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%lf %lf\n", x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = -1.5; x[1] = 0.0;
	printf("초기값2: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값2: %.2lf %.2lf\n", x[0], x[1]);
	hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	printf("%lf %lf\n", x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%lf %lf\n", x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = 1.5; x[1] = 2.0;
	printf("초기값3: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값3: %.2lf %.2lf\n", x[0], x[1]);
	hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	printf("%lf %lf\n", x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%lf %lf\n", x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	x[0] = 2.5; x[1] = -3.0;
	printf("초기값4: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값4: %.2lf %.2lf\n", x[0], x[1]);
	hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	printf("%lf %lf\n", x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	fprintf(fp_w, "%lf %lf\n", x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);
	/********************************/

	fclose(fp_w);
}