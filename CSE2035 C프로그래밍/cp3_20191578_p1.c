#include <stdio.h>
void swap(int *a, int *b);
void sort(int *a, int n);
void print_array(int *a, int n);

int main(void){
	int n;
	int array[1000];
	scanf("%d", &n);
	for(int i=0;i<n;i++)
		scanf("%d", array+i);
	sort(array, n);
	print_array(array, n);
	
	return 0;}

void swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;}

void sort(int *a, int n){
	for(int i=n-1;i>0;i--){
		for(int j=0;j<i;j++){
			if(*(a+j)>*(a+j+1)){
				swap(a+j, a+j+1);
		}}
	}
}

void print_array(int *a, int n){
	for(int i=0;i<n;i++)
		printf("%d ", *(a+i));
	printf("\n");
}
