#include "my_solver.h"
#include <time.h>
#include <cmath>

// HOMEWORK
void program2_3()
{
	/* 셋 중 하나 실행 */
	program2_2_a();
	//program2_2_b();
	//program2_2_c();

	/* 파일 열기 */
	FILE* fp_r_pdf, *fp_r_random, * fp_w;
	fp_r_pdf = fopen("pdf_table.txt", "r");
	fp_r_random = fopen("random_event_table.txt", "r");
	fp_w = fopen("histogram.txt", "w");

	/* pdf 파일 열어서 확률 밀도 함수 읽기 */
	int n;
	double h;
	fscanf(fp_r_pdf, "%d %lf", &n, &h);
	double* x = (double*)malloc(sizeof(double) * n);
	double* y = (double*)malloc(sizeof(double) * n);
	int i = 0;
	while (EOF != fscanf(fp_r_pdf, "%lf %lf", &x[i], &y[i])) {
		i++;
	}

	/* 생성된 난수 읽기 */
	int nr;
	fscanf(fp_r_random, "%d", &nr);
	double* random_X = (double*)malloc(sizeof(double) * nr);
	i = 0;
	while (EOF != fscanf(fp_r_random, "%lf", &random_X[i])) {
		i++;
	}

	/* x축 구간 나누기 */
	double x_section[20];
	for (i = 0; i < 20; i++) {
		x_section[i] = 0;
	}
	
	/* 구간에 몇개의 난수가 생성되었는가? */
	for (i = 0; i < nr; i++) {
		int index = random_X[i] * 20;
		x_section[index]++;
	}

	/* 히스토그램 그리기 */
	for (i = 0; i < 20; i++) {
		fprintf(fp_w, "[%.2lf, %.2lf)\t", (double)i/20, ((double)i + 1)/20);
		for (int j = 0; j < x_section[i]; j++) {
			fprintf(fp_w, "#");
		}
		fprintf(fp_w, "\n");
	}

	/* 파일 닫기 */
	if (fp_r_pdf != NULL) fclose(fp_r_pdf);
	if (fp_r_random != NULL) fclose(fp_r_random);
	if (fp_w != NULL) fclose(fp_w);
}

// HOMEWORK
void program2_2_a()
{
	__int64 start, freq, end;
	float resultTime = 0;

	int nr = 0;
	printf("생성할 난수의 개수: ");
	scanf("%d", &nr);

	CHECK_TIME_START;

	// something to do...
	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	int n;
	double h;

	fscanf(fp_r, "%d %lf", &n, &h);

	double* x = (double*)malloc(sizeof(double) * n);
	double* y = (double*)malloc(sizeof(double) * n);
	int i = 0;

	while (EOF != fscanf(fp_r, "%lf %lf", &x[i], &y[i])) {
		i++;
	}

	fprintf(fp_w, "%d\n", nr);

	i = 0;
	double U;
	double X;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	while (i < nr) {
		U = (double)rand() / MY_RAND_MAX;
		X = Bisection(0, 1, U, y, h, x, n);
		fprintf(fp_w, "%.15lf\n", X);
		//printf("%.15lf\n", X);
		i++;
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	CHECK_TIME_END(resultTime);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_b()
{
	__int64 start, freq, end;
	float resultTime = 0;

	int nr = 0;
	printf("생성할 난수의 개수: ");
	scanf("%d", &nr);

	CHECK_TIME_START;

	// something to do...
	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	int n;
	double h;

	fscanf(fp_r, "%d %lf", &n, &h);

	double* x = (double*)malloc(sizeof(double) * n);
	double* y = (double*)malloc(sizeof(double) * n);
	int i = 0;

	while (EOF != fscanf(fp_r, "%lf %lf", &x[i], &y[i])) {
		i++;
	}
	
	fprintf(fp_w, "%d\n", nr);

	i = 0;
	double U;
	double X;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	while (i < nr) {
		U = (double)rand() / MY_RAND_MAX;
		X = Secant(0, 1, U, y, h, x, n);
		fprintf(fp_w, "%.15lf\n", X);
		//printf("%.15lf\n", X);
		i++;
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	CHECK_TIME_END(resultTime);

	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_c()
{
	__int64 start, freq, end;
	float resultTime = 0;

	int nr = 0;
	printf("생성할 난수의 개수: ");
	scanf("%d", &nr);

	CHECK_TIME_START;

	// something to do...
	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	int n;
	double h;

	fscanf(fp_r, "%d %lf", &n, &h);

	double* x = (double*)malloc(sizeof(double) * n);
	double* y = (double*)malloc(sizeof(double) * n);
	int i = 0;

	while (EOF != fscanf(fp_r, "%lf %lf", &x[i], &y[i])) {
		i++;
	}

	fprintf(fp_w, "%d\n", nr);

	i = 0;
	double U;
	double X;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	while (i < nr) {
		U = (double)rand() / MY_RAND_MAX;
		double initial_X = Bisection(0, 1, U, y, h, x, n) + U;
		//printf("%lf\n", initial_X);
		X = Newton(initial_X, U, y, h, x, n);
		//X = Newton(0.5, U, y, h, x, n);
		fprintf(fp_w, "%.15lf\n", X);
		//printf("%.15lf\n", X);
		i++;
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	CHECK_TIME_END(resultTime);

	printf("The program2_2_c run time is %f(ms)..\n", resultTime * 1000.0);
}

double Secant(double aa, double bb, double U, double* y, double h, double* x, int n) {
	double xn[100];
	int index = 0;
	xn[0] = aa;
	xn[1] = bb;
	for (int i = 2; i < Nmax; i++) {
		xn[i] = xn[i - 1] - newfunction(xn[i - 1], U, y, h, x, n) * (xn[i - 1] - xn[i - 2]) / (newfunction(xn[i - 1], U, y, h, x, n) - newfunction(xn[i - 2], U, y, h, x, n));
		if (abs(newfunction(xn[i], U, y, h, x, n)) < DELTA || i>= Nmax || abs(xn[i] - xn[i - 1]) < EPSILON) {
			index = i;
			break;
		}
	}
	return xn[index];
}

double Newton(double aa, double U, double* y, double h, double* x, int n) {
	double x0, x1;
	int index = 0;
	double xn[100];
	double Px, Px1, s, prime;
	xn[0] = aa;

	for (int i = 1; i < Nmax; i++) {
		//Px = newfunction(xn[i], U, y, h, x, n);
		//Px1 = newfunction(xn[i + 1], U, y, h, x, n);
		s = (xn[i - 1] - xn[i - 1]) / (xn[i] - xn[i - 1]);
		Px = y[i - 1];
		Px1 = y[i];
		prime = (1 - s) * Px + s * Px1;
		//printf("Px: %lf, Px+1: %lf, s: %lf, prime: %lf\n", Px, Px1, s, prime);
		xn[i] = xn[i - 1] - newfunction(xn[i - 1], U, y, h, x, n) / prime;
		//printf("%lf\n", xn[i]);
		if (abs(newfunction(xn[i], U, y, h, x, n)) < DELTA || i >= Nmax || abs(xn[i] - xn[i - 1]) < EPSILON) {
			index = i;
			break;
		}
	}
	return xn[index];
}