#include <stdio.h>
void swap(int *a, int *b);
void sort(int *a, int m);
void all_sort(int a[][100], int n, int m);

int main(void){
	int N,M;
	int array[100][100];
	scanf("%d %d", &N, &M);
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++)
			scanf("%d", *(array+i)+j);} 
	all_sort(array, N,M);

	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++)
			printf("%d ", *(*(array+i)+j));
		printf("\n");}

	return 0;}

void swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;}

void sort(int *a, int m){
	for(int i=m-1;i>0;i--){
		for(int j=0;j<i;j++){
			if(*(a+j)>*(a+j+1))
				swap((a+j), (a+j+1));}}}

void all_sort(int a[][100], int n, int m){
	for(int i=0;i<n;i++)
		sort(*(a+i), m);
}
