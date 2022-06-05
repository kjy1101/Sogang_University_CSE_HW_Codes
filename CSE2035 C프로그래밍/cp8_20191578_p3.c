#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n;
	int **ground;
	scanf("%d", &n);
	ground=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		ground[i]=(int*)malloc(n*sizeof(int));

	int row=0;
	int col=n/2;
	int num=1;
	ground[row][col]=num;

	while(1){
		num++;
		if(num%n==1){
			row++;
			if(row==n) row=0;
			ground[row][col]=num;}
		else{
			row--;
			col++;
			if(row<0) row=n-1;
			if(col==n) col=0;
			ground[row][col]=num;
		}
		if(num==n*n) break;
	}


	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%3d", ground[i][j]);
		printf("\n");}

	free(ground);

	return 0;}
