#include <stdio.h>

int main(void){
	int n, i=2, temp;
	printf("Input: ");
	scanf("%d", &n);
	temp = n;
	n = 2*n + 1;
	while (i < n){
		int j;
		j = temp;
		while (j > 1){
			printf(" ");
			j--;}
		temp-=1;
		j = 1;
		while (j < i){
			printf("*");
			j++;}
		printf("\n");
		i+=2;}
	return 0;}
