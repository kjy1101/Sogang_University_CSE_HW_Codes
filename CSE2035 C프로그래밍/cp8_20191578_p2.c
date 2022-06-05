#include <stdio.h>
#include <stdlib.h>
int determinant(int **a);//행렬 A의 (ad-bc)를 계산하여 반환

int main(void){
	int **matrix;
	float **result,det;

	matrix=(int**)malloc(2*sizeof(int*));
	for(int i=0;i<2;i++)
		matrix[i]=(int*)malloc(2*sizeof(int));

	result=(float**)malloc(2*sizeof(float*));
	for(int i=0;i<2;i++)
		result[i]=(float*)malloc(2*sizeof(float));


	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++)
			scanf("%d", &matrix[i][j]);}

	det=(float)determinant(matrix);

	if(det==0) printf("Singular matrix\n");

	else{
		printf("Invertible matrix\n");
		result[0][0]=(float)matrix[1][1]/det;
		result[0][1]=(float)matrix[0][1]/det*(-1);
		result[1][0]=(float)matrix[1][0]/det*(-1);
		result[1][1]=(float)matrix[0][0]/det;

		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++)
				printf("%.2f ", (float)result[i][j]);
			printf("\n");}
	}
	
	free(matrix);
	free(result);

	return 0;}

int determinant(int **a){
	int det;
	det=a[0][0]*a[1][1]-a[0][1]*a[1][0];
	return det;
}
