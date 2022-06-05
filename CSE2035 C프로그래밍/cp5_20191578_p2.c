#include <stdio.h>
#include <stdlib.h>
int *calculate_next(int *pascal_tr, int current_level);
int factorial(int n);

int main(void){
	int n;
	printf("Input the level of Pascal's triangle : ");
	scanf("%d", &n);
	int *pascal_tr;
	printf("\n");
	for(int i=0;i<n;i++){
		pascal_tr=malloc(i*sizeof(int));
		calculate_next(pascal_tr, i);
		for(int j=0;j<=i;j++)
			printf("%d ", pascal_tr[j]);
		printf("\n");}

	free(pascal_tr);

	return 0;}

int *calculate_next(int *pascal_tr, int current_level){
	for(int i=0;i<=current_level;i++){
		pascal_tr[i]=factorial(current_level)/(factorial(i)*factorial(current_level-i));
}
	return pascal_tr;}

int factorial(int n){
	int result=1;
	for(int i=1;i<=n;i++)
		result*=i;
	return result;}
