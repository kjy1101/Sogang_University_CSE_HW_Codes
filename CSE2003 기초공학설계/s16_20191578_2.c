#include <stdio.h>

int main(void){
	int n, i, Fibo;
	scanf("%d", &n);
	int n1=0;
	int n2=1;
	for (i=1;i<n;i++){
		Fibo=n1+n2;
		n1 = n2;
		n2 = Fibo;}
	printf("%d\n", Fibo);
	return 0;}


