#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <cmath>
#define DELTA 0.000001
#define Nmax 50
#define EPSILON 0.00001
#define MY_RAND_MAX 32767
double Bisection(double aa, double bb, double U, double *y, double h, double* x, int n);
double newfunction(double xx, double U, double *y, double h, double *x, int n);

void program2_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	int n;
	double h;

	fscanf(fp_r, "%d %lf", &n, &h);

	double* x = (double*)malloc(sizeof(double) * n);
	double* y = (double*)malloc(sizeof(double) * n);
	int i = 0;

	while (EOF != fscanf(fp_r, "%lf %lf", &x[i], &y[i])) {
		i++;
	}

	int nr = 0;
	printf("생성할 난수의 개수: ");
	scanf("%d", &nr);
	fprintf(fp_w, "%d\n", nr);

	i = 0;
	//double irand;
	double U;
	double X;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);
	
	while (i < nr) {
		U = (double)rand()/MY_RAND_MAX;
		X = Bisection(0, 1, U, y, h, x, n); //초기값 0,1과 변수 U
		fprintf(fp_w, "%.15lf\n", X);
		i++;
	}
	

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}


double Bisection(double aa, double bb, double U, double* y, double h, double* x, int n) {
	double p[100], a[100], b[100];
	//printf("U:%lf\n", U);
	a[1] = aa;
	b[1] = bb;
	p[0] = aa;
	int index=0;
	double fx = 0, gx = 0;
	for (int i = 1; i < Nmax; i++) {
		p[i] = (a[i] + b[i]) / 2;
		fx = newfunction(p[i], U, y, h, x, n);
		gx = newfunction(a[i], U, y, h, x, n);
		if (abs(p[i] - p[i - 1]) < EPSILON || abs(fx) < DELTA) {
			index = i;
			break;
		}
		if (fx * gx > 0) {
			a[i + 1] = p[i];
			b[i + 1] = b[i];
		}
		else {
			a[i + 1] = a[i];
			b[i + 1] = p[i];
		}
	}
	return p[index];
}

double newfunction(double xx, double U, double* y, double h, double* x, int n) {
	
	int x_index = 0;
	for (int i = 1; i < n; i++) {
		if (x[i] > xx) {
			x_index = i - 1;
			break;
		}
	}
	
	double integral_fx = y[0] + y[x_index - 1];
	double mid_term = 0;
	for (int j = 1; j < x_index - 1; j++) {
		mid_term += y[j];
	}
	integral_fx += (2 * mid_term);
	double result = integral_fx * h / 2;
	
	if (x[x_index] < xx) {
		double remain = (y[x_index] + ((y[x_index + 1] - y[x_index]) / (x[x_index + 1] - x[x_index])) * ((xx - x[x_index]) / 2)) * (xx - x[x_index]);
		result += remain;
	}
	
	result -= U;
	return result;
}