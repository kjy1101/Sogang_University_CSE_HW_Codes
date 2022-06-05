#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n;
	int **pascal;
	printf("Input the level of Pascal's triangle : ");
	scanf("%d",&n);
	pascal=(int**)calloc(n,sizeof(int*));
	for(int i=0;i<n;i++)
		pascal[i]=(int*)calloc(n,sizeof(int));
	for(int i=0;i<n;i++)
		pascal[i][0]=1;

	for(int i=1;i<n;i++){
		for(int j=1;j<=i;j++)
			pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];}
	printf("\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++)
			printf("%d ", pascal[i][j]);
		printf("\n");}
	free(pascal);

	return 0;}
