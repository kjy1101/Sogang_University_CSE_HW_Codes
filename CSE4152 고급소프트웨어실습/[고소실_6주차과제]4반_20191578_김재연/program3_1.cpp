#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

double GPS_signal[22];

extern "C"
{
	int hybrj1_(void fcn(int*, double*, double*, double*, int*, int*), int*, double*, double*, double*, int*, double*, int*, double*, int*);
	int hybrd1_(void fcn(int*, double*, double*, int*), int*, double*, double*, double*, int*, double*, int*);
}

void fcn3_1_1(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = pow(x[0] - GPS_signal[2], 2) + pow(x[1] - GPS_signal[3], 2) + pow(x[2] - GPS_signal[4], 2) - pow(GPS_signal[0] * (GPS_signal[6] + x[3] - GPS_signal[5]), 2);
		fvec[1] = pow(x[0] - GPS_signal[7], 2) + pow(x[1] - GPS_signal[8], 2) + pow(x[2] - GPS_signal[9], 2) - pow(GPS_signal[0] * (GPS_signal[11] + x[3] - GPS_signal[10]), 2);
		fvec[2] = pow(x[0] - GPS_signal[12], 2) + pow(x[1] - GPS_signal[13], 2) + pow(x[2] - GPS_signal[14], 2) - pow(GPS_signal[0] * (GPS_signal[16] + x[3] - GPS_signal[15]), 2);
		fvec[3] = pow(x[0] - GPS_signal[17], 2) + pow(x[1] - GPS_signal[18], 2) + pow(x[2] - GPS_signal[19], 2) - pow(GPS_signal[0] * (GPS_signal[21] + x[3] - GPS_signal[20]), 2);
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 2 * (x[0] - GPS_signal[2]);	fjac[4] = 2 * (x[1] - GPS_signal[3]);		fjac[8] = 2 * (x[2] - GPS_signal[4]);	fjac[12] = -2 * GPS_signal[0] * GPS_signal[0] * (GPS_signal[6] + x[3] - GPS_signal[5]);
		fjac[1] = 2 * (x[0] - GPS_signal[7]);	fjac[5] = 2 * (x[1] - GPS_signal[8]);		fjac[9] = 2 * (x[2] - GPS_signal[9]);	fjac[13] = -2 * GPS_signal[0] * GPS_signal[0] * (GPS_signal[11] + x[3] - GPS_signal[10]);
		fjac[2] = 2 * (x[0] - GPS_signal[12]);	fjac[6] = 2 * (x[1] - GPS_signal[13]);		fjac[10] = 2 * (x[2] - GPS_signal[14]);	fjac[14] = -2 * GPS_signal[0] * GPS_signal[0] * (GPS_signal[16] + x[3] - GPS_signal[15]);
		fjac[3] = 2 * (x[0] - GPS_signal[17]);	fjac[7] = 2 * (x[1] - GPS_signal[18]);		fjac[11] = 2 * (x[2] - GPS_signal[19]);	fjac[15] = -2 * GPS_signal[0] * GPS_signal[0] * (GPS_signal[21] + x[3] - GPS_signal[20]);
		/********************************/
	}
}

void fcn3_1_2(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = pow(x[0] - GPS_signal[2], 2) + pow(x[1] - GPS_signal[3], 2) + pow(x[2] - GPS_signal[4], 2) - pow(GPS_signal[0] * (GPS_signal[6] + x[3] - GPS_signal[5]), 2);
	fvec[1] = pow(x[0] - GPS_signal[7], 2) + pow(x[1] - GPS_signal[8], 2) + pow(x[2] - GPS_signal[9], 2) - pow(GPS_signal[0] * (GPS_signal[11] + x[3] - GPS_signal[10]), 2);
	fvec[2] = pow(x[0] - GPS_signal[12], 2) + pow(x[1] - GPS_signal[13], 2) + pow(x[2] - GPS_signal[14], 2) - pow(GPS_signal[0] * (GPS_signal[16] + x[3] - GPS_signal[15]), 2);
	fvec[3] = pow(x[0] - GPS_signal[17], 2) + pow(x[1] - GPS_signal[18], 2) + pow(x[2] - GPS_signal[19], 2) - pow(GPS_signal[0] * (GPS_signal[21] + x[3] - GPS_signal[20]), 2);
	/********************************/
}

void program3_1(void) {
	program3_1_1();
	program3_1_2();
}

void program3_1_1(void) {
	printf("=========== program3_1_1 ===========\n");

	char readfile[256];
	char writefile[256];

	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.0, 0.0, 0.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
	double fresult[SOLNUMS];

	for (int t = 0; t <= 2; t++) {

		sprintf(readfile, "GPS_signal_%d.txt", t);
		sprintf(writefile, "GPS_position_3-1_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		//double GPS_signal[22];
		int i = 0;
		while (EOF != fscanf(fp_r, "%lf", &GPS_signal[i])) {
			i++;
		}
		
		printf("초기값 입력(3개): ");
		scanf("%lf %lf %lf", &x[0], &x[1], &x[2]);
		x[3] = GPS_signal[1];
		fprintf(fp_w, "초기값: %.2lf %.2lf %.2lf %.2lf\n", x[0], x[1], x[2], x[3]);

		hybrj1_(fcn3_1_1, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
		printf("%lf %lf %lf %lf\n", x[0], x[1], x[2], x[3]);
		printf("f1=%lf, f2=%lf, f3=%lf, f4=%lf\n\n", fvec[0], fvec[1], fvec[2], fvec[3]);

		fprintf(fp_w, "%lf %lf %lf %lf\n", x[0], x[1], x[2], x[3]);
		fprintf(fp_w, "f1=%lf, f2=%lf, f3=%lf, f4=%lf\n\n", fvec[0], fvec[1], fvec[2], fvec[3]);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
	printf("====================================\n\n");
}

void program3_1_2(void) {
	printf("=========== program3_1_2 ===========\n");
	char readfile[256];
	char writefile[256];

	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.0, 0.0, 0.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	for (int t = 0; t <= 2; t++) {

		sprintf(readfile, "GPS_signal_%d.txt", t);
		sprintf(writefile, "GPS_position_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		//double GPS_signal[22];
		int i = 0;
		while (EOF != fscanf(fp_r, "%lf", &GPS_signal[i])) {
			i++;
		}

		printf("초기값 입력(3개): ");
		scanf("%lf %lf %lf", &x[0], &x[1], &x[2]);
		x[3] = GPS_signal[1];
		fprintf(fp_w, "초기값: %.2lf %.2lf %.2lf %.2lf\n", x[0], x[1], x[2], x[3]);

		hybrd1_(fcn3_1_2, &n, x, fvec, &tol, &info, wa, &lwa);
		printf("%d %lf %lf %lf %lf\n", info, x[0], x[1], x[2], x[3]);
		printf("f1=%lf, f2=%lf, f3=%lf, f4=%lf\n\n", fvec[0], fvec[1], fvec[2], fvec[3]);

		fprintf(fp_w, "%d %lf %lf %lf %lf\n", info, x[0], x[1], x[2], x[3]);
		fprintf(fp_w, "f1=%lf, f2=%lf, f3=%lf, f4=%lf\n\n", fvec[0], fvec[1], fvec[2], fvec[3]);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
	printf("====================================\n");
}