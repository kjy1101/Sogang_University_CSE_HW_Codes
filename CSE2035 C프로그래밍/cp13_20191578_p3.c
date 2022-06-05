#include <stdio.h>

struct complex{
	float real;
	float imag;
}complex;

struct complex add(struct complex n1, struct complex n2);

int main(void){
	float n1_real, n1_imag;
	float n2_real, n2_imag;
	scanf("%f %f", &n1_real, &n1_imag);
	scanf("%f %f", &n2_real, &n2_imag);

	struct complex n1={n1_real, n1_imag};
	struct complex n2={n2_real, n2_imag};
	struct complex result={add(n1,n2).real, add(n1,n2).imag};
	
	printf("Sum = %.1f + %.1fi\n", result.real, result.imag);

	return 0;}

struct complex add(struct complex n1, struct complex n2){
	struct complex result;
	result.real=n1.real+n2.real;
	result.imag=n1.imag+n2.imag;
	return result;}
