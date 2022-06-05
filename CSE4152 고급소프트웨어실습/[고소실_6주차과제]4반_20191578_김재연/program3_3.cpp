#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001
#define PI 3.141592653589

extern "C"
{
	int hybrj1_(void fcn(int*, double*, double*, double*, int*, int*), int*, double*, double*, double*, int*, double*, int*, double*, int*);
}

void fcn3_3(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = sin(x[0] * x[1] + PI / 6) + sqrt(x[0] * x[0] * x[1] * x[1] + 1) + 2.8 * cos(x[0] - x[1]);
		fvec[1] = x[0] * exp(x[0] * x[1] + PI / 6) - sin(x[0] - x[1]) - 1.66 * sqrt(x[0] * x[0] * x[1] * x[1] + 1);
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = (x[0] * x[1] * x[1]) / sqrt(x[0] * x[0] * x[1] * x[1] + 1) - 2.8 * sin(x[0] - x[1]) + x[1] * cos(x[0] * x[1] + PI / 6);	fjac[2] = (x[0] * x[0] * x[1]) / sqrt(x[0] * x[0] * x[1] * x[1] + 1) + 2.8 * sin(x[0] - x[1]) + x[0] * cos(x[0] * x[1] + PI / 6);
		fjac[1] = (-1.66 * x[0] * x[1] * x[1]) / sqrt(x[0] * x[0] * x[1] * x[1] + 1) + x[0] * x[1] * exp(x[0] * x[1] + PI / 6) + exp(x[0] * x[1] + PI / 6) - cos(x[0] - x[1]);	fjac[3] = (-1.66 * x[0] * x[0] * x[1]) / sqrt(x[0] * x[0] * x[1] * x[1] + 1) + x[0] * x[0] * exp(x[0] * x[1] + PI / 6) + cos(x[0] - x[1]);
		/********************************/
	}
}

void program3_3(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 20.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
	double fresult[SOLNUMS];

	FILE* fp_w = fopen("roots_found_3-3.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_found_3-3.txt");
		return;
	}

	printf("초기값: %.2lf %.2lf\n", x[0], x[1]);
	fprintf(fp_w, "초기값: %.2lf %.2lf\n", x[0], x[1]);

	hybrj1_(fcn3_3, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	printf("%lf %lf\n", x[0], x[1]);
	printf("f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

	fprintf(fp_w, "%lf %lf\n", x[0], x[1]);
	fprintf(fp_w, "f1=%lf, f2=%lf\n\n", fvec[0], fvec[1]);

}