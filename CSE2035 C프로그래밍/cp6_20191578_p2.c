#include <stdio.h>
#include <stdlib.h>

int main(void){
	int N;
	int *binary;
	scanf("%d", &N);
	int temp=N;
	int size=0;
	while(temp>=1){
		temp/=2;
		size++;}
	binary=malloc(size*sizeof(int));

	for(int i=0;i<size;i++){
		binary[i]=N%2;
		N/=2;}
	for(int i=size-1;i>=0;i--)
		printf("%d", binary[i]);
	printf("\n");
	free(binary);

	return 0;}
