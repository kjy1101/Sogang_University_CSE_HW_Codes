#include <stdio.h>
#include <stdlib.h>
void push_back(int **a, int *size, int value);
void pop_back(int **a, int *size);
double average(int *a, int size);
double variance(int *a, int size);

int main(void){
	int N;
	int order, add_number, size=0;
	double avg, var;
	int *array;
	array=(int*)malloc(0);
	scanf("%d", &N);
	for(int i=0;i<N;i++){
		scanf("%d", &order);
		if(order==1){
			scanf("%d", &add_number);
			push_back(&array, &size, add_number);
		}
		else
			pop_back(&array, &size);
		avg=average(array, size);
		var=variance(array, size);
		for(int j=0;j<size;j++)
			printf("%d ", array[j]);
		printf("\n");
		printf("%f %f\n", avg, var);
	}
	free(array);
	return 0;}

void push_back(int **a, int *size, int value){
	(*size)++;
	*a=(int*)realloc(*a, *size*sizeof(int));
	*(*a+*size-1)=value;
}
void pop_back(int **a, int *size){
	if(*size==0) return;
	(*size)-=1;
	*a=(int*)realloc(*a, *size*sizeof(int));
}

double average(int *a, int size){
	if(size==0) return 0.0;
	double sum=0;
	for(int i=0;i<size;i++)
		sum+=*(a+i);
	sum/=size;
	return sum;}

double variance(int *a, int size){
	if(size==0) return 0.0;
	//분산=편차의 제곱의 평균
	double avg;
	avg=average(a, size);
	double sum=0;
	double dev_square;
	for(int i=0;i<size;i++){
		dev_square=(*(a+i)-avg)*(*(a+i)-avg);
		sum+=dev_square;}
	sum/=size;
	return sum;}
