#include <stdio.h>

void swap(int *a, int *b);
void sort(int *a, int m);
void all_sort(int a[][100], int n, int m);
int binary_search(int *a, int *endPtr, int key, int **findPtr);
int all_binary_search(int a[][100], int n, int m, int key, int **findPtr);

int main(void){
	int N,M,K;
	int matrix[100][100];
	int *findPtr;
	int result;
	scanf("%d %d %d", &N, &M, &K);
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++)
			scanf("%d", *(matrix+i)+j);}
	all_sort(matrix, N, M);
	result=all_binary_search(matrix, N, M, K, &findPtr);
	printf("%d\n",result);
	if(result==1)
		printf("%p\n",findPtr);

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
				swap(a+j, a+j+1);}}}

void all_sort(int a[][100], int n, int m){
	for(int i=0;i<n;i++)
		sort(*(a+i), m);}

int binary_search(int *a, int *endPtr, int key, int **findPtr){
	int *firstPtr;
	int *midPtr;
	int *lastPtr;
	firstPtr=a;
	lastPtr=endPtr;
	while(firstPtr<=lastPtr){
		midPtr=firstPtr + (lastPtr-firstPtr)/2;
		if(key>*midPtr)
			firstPtr=midPtr+1;
		else if(key<*midPtr)
			lastPtr=midPtr-1;
		else
			firstPtr=lastPtr+1;
	}
	*findPtr=midPtr;
	return (key==*midPtr);
}

int all_binary_search(int a[][100], int n, int m, int key, int **findPtr){
	int result;
	int count=0;
	for(int i=0;i<n;i++){
		result=binary_search(*(a+i), *(a+i)+m-1, key, findPtr);
		if(result==1)
			count++;}
	if(count>0) return 1;
	else return 0;
}
