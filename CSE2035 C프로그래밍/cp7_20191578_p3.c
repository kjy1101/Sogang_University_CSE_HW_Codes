#include <stdio.h>
#include <stdlib.h>
void double_double(int **a, int *size);
int bubble(int *a, int size);
void swap(int *a, int *b);

int main(void){
	int N;
	int *array;
	scanf("%d", &N);
	array=(int*)calloc(N, sizeof(int));
	for(int i=0;i<N;i++)
		scanf("%d", &array[i]);
	for(int j=0;j<3;j++){
	double_double(&array, &N);
	for(int i=0;i<N;i++)
		printf("%d ", array[i]);
	printf("\n");}
	free(array);
	return 0;}

void swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;}

int bubble(int *a, int size){
	for(int i=size-1;i>0;i--){
		for(int j=0;j<i;j++){
			if(*(a+j)>*(a+j+1))
				swap(a+j, a+j+1);}}
}

void double_double(int **a, int *size){
	int temp=*size;
	(*size)*=2;
	*a=(int*)realloc(*a, *size*sizeof(int));
	for(int i=temp;i<*size;i++){
		*(*a+i)=*(*a+i-temp)*2;
	}
	bubble(*a, *size);
}
