#include <stdio.h>

float average(int matrix[100][100], int columnindex, int n);

int main(void){
	int n,i,k;
	float avg;

	scanf("%d", &n);

	int matrix[100][100];

	for (i=0;i<n;i++){
		for (k=0;k<n;k++){
			scanf("%d", &matrix[i][k]);}}
	for (i=0;i<n;i++){
			avg = average(matrix, i, n);
			printf("%.2f ", avg);}
	printf("\n");

	return 0;}


float average(int matrix[100][100], int columnindex, int n){
	int i, total=0;
	for(i=0;i<n;i++){
		total += matrix[columnindex][i];}
	return (float)total/n;}
