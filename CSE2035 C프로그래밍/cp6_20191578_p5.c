#include <stdio.h>
#include <stdlib.h>

int main(void){
	int **matrixA, **matrixB, **result;
	int N;
	scanf("%d", &N);
	matrixA=(int**)malloc(sizeof(int*)*N);
	matrixB=(int**)malloc(sizeof(int*)*N);
	result=(int**)malloc(sizeof(int*)*N);
	for(int i=0;i<N;i++){
		*(matrixA+i)=(int*)malloc(sizeof(int)*N);
		*(matrixB+i)=(int*)malloc(sizeof(int)*N);
		*(result+i)=(int*)malloc(sizeof(int)*N);}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			scanf("%d", &matrixA[i][j]);}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			scanf("%d", &matrixB[i][j]);}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<N;k++){
				result[i][j]+=matrixA[i][k]*matrixB[k][j];}}}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			printf("%d ", result[i][j]);
		printf("\n");}

	free(matrixA);
	free(matrixB);
	free(result);

	return 0;}
