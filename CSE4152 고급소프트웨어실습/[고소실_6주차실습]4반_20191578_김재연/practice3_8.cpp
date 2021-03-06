#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_8(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = 3 * x[0] - cos(x[1] * x[2]) - 0.5;
		fvec[1] = x[0] * x[0] - 81 * (x[1] + 0.1) * (x[1] + 0.1) + sin(x[2]) + 1.06;
		fvec[2] = exp(-1 * x[0] * x[1]) + 20 * x[2] + (10 * 3.141592653589 - 3) / 3;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 3.0;									fjac[3] = x[2] * sin(x[1] * x[2]);				fjac[6] = x[1] * sin(x[1] * x[2]);
		fjac[1] = 2.0 * x[0];							fjac[4] = -162 * (x[1] + 0.1);					fjac[7] = cos(x[2]);
		fjac[2] = -1 * x[1] * exp(-1 * x[0] * x[1]);	fjac[5] = -1 * x[0] * exp(-1 * x[0] * x[1]);	fjac[8] = 20;
		/********************************/
	}
}

void practice3_8(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.1, 0.1, -0.1 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-8.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-8.txt");
		return;
	}

	/********************************/
	printf("초기값: %.2lf %.2lf %.2lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "초기값: %.2lf %.2lf %.2lf\n", x[0], x[1], x[2]);
	hybrj1_(fcn3_8, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	printf("%lf %lf %lf\n", x[0], x[1], x[2]);
	printf("f1=%lf, f2=%lf, f3=%lf\n\n", fvec[0], fvec[1], fvec[2]);
	fprintf(fp_w, "%lf %lf %lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "f1=%lf, f2=%lf, f3=%lf\n\n", fvec[0], fvec[1], fvec[2]);
	/********************************/

	fclose(fp_w);
}
