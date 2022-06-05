#include "my_solver.h"
#include <cmath>

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	double x0, x1;
	int n;
	double xn[100];

	if (fp == NULL)
		return;

	scanf("%lf", &x0); //�ʱⰪ
	xn[0] = x0;

	printf("n\t\txn1\t\t\t|f(xn1)|\n");
	printf("%d\t%.15e\t%.15e\n", 0, xn[0], abs(_f(xn[0])));

	fprintf(fp, "n\t\txn1\t\t\t|f(xn1)|\n");
	fprintf(fp, "%d\t%.15e\t%.15e\n", 0, xn[0], abs(_f(xn[0])));

	for (int i = 1; i < 100; i++) {
		xn[i] = xn[i - 1] - _f(xn[i - 1]) / _fp(xn[i - 1]);
		printf("%d\t%.15e\t%.15e\n", i, xn[i], abs(_f(xn[i])));
		fprintf(fp, "%d\t%.15e\t%.15e\n", i, xn[i], abs(_f(xn[i])));
		if (abs(_f(xn[i])) < DELTA) return;
		if (i >= Nmax) return;
		if (abs(xn[i] - xn[i - 1]) < EPSILON) return;
	}
}
