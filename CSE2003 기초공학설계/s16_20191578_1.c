#include <stdio.h>

void func_gcd(int a, int b, int *gcd);
int main (void){
	int first, second, gcd;
	printf("Input first number: ");
	scanf("%d", &first);
	printf("Input second number: ");
	scanf("%d", &second);

	func_gcd(first, second, &gcd);

	printf("GCD: %d\n", gcd);

	return 0;}

void func_gcd(int a, int b, int *gcd){
	while (b > 0){
		int temp = a;
		a = b;
		b = temp % b;}
	*gcd = a;}

