#include "my_solver.h"
#include <cmath>

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/
void program1_3(FILE *fp)
{
	double a0, b0, x0, x1 , temp;
	int n;
	double p[100], a[100], b[100];

	if (fp == NULL)
		return;

	scanf("%lf %lf", &a0, &b0); //�ʱⰪ
	a[1] = a0;
	b[1] = b0;
	p[0] = a0;

	printf("n\t\txn1\t\t\t|f(xn1)|\n");
	printf("%d\t%.15e\t%.15e\n", 0, p[0], abs(_f(p[0])));

	fprintf(fp, "n\t\txn1\t\t\t|f(xn1)|\n");
	fprintf(fp, "%d\t%.15e\t%.15e\n", 0, p[0], abs(_f(p[0])));

	for (int i = 1; i < 99; i++) {
		p[i] = (a[i] + b[i]) / 2;
		printf("%d\t%.15e\t%.15e\n", i, p[i], abs(_f(p[i])));
		fprintf(fp, "%d\t%.15e\t%.15e\n", i, p[i], abs(_f(p[i])));
		if (abs(p[i] - p[i - 1]) < EPSILON || abs(_f(p[i])) < EPSILON) return;
		if (_f(p[i]) * _f(a[i]) > 0) {
			a[i + 1] = p[i];
			b[i + 1] = b[i];
		}
		else {
			a[i + 1] = a[i];
			b[i + 1] = p[i];
		}
	}
	
}