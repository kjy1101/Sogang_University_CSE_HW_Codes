#include <stdio.h>
#include <math.h>

float approx_exfunc(float x);
int giveme_factorial(int n);

int main(void){
	float x;
	scanf("%f", &x);

	printf("%f\n", approx_exfunc(x));

	return 0;}


float approx_exfunc(float x){
	int k;
	float result =0;
	for (k=0;k<10;k++){
		result += pow(x,k)/giveme_factorial(k);}
	return result;}

int giveme_factorial(int n){
	int i = 1, fact=1;
	while (i <= n){
		fact *= i;
		i++;}
	return fact;}





//int giveme_factorial(int n){
//	if (n==0)
//		return 1;
//	else
//		return n*giveme_factorial(n-1);}
