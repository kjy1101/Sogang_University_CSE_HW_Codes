#include <stdio.h>
#include <stdlib.h>

typedef struct{
	float real;
	float imag;
} complex;

complex *multiple(complex *a, complex *b);

int main(void){
	complex a, b;
	complex *result;
	scanf("%f %f", &(a.real), &(a.imag));
	scanf("%f %f", &(b.real), &(b.imag));
	result=multiple(&a, &b);
	printf(" %.2f + (%.2f)i\n", result->real, result->imag);
	return 0;}

complex *multiple(complex *a, complex *b){
	complex *r;
	r=(complex*)malloc(sizeof(complex));
	r->real=(a->real)*(b->real)-(a->imag)*(b->imag);
	r->imag=(a->real)*(b->imag)+(a->imag)*(b->real);
	return r;
}
