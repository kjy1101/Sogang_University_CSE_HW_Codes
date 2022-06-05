#include <stdio.h>
void shift_n_right(int *a, int n);
void print_array(int *a);

int main(void){
	int n;
	int array[10]={1,2,3,4,5,6,7,8,9,10};
	scanf("%d", &n);
	shift_n_right(array, n);
	print_array(array);

	return 0;}

void shift_n_right(int *a, int n){
	for(int i=0;i<10;i++){
		*(a+i)+=(10-n);
		if(*(a+i)>10)
			*(a+i)-=10;}

}

void print_array(int *a){
	for(int i=0;i<10;i++)
		printf("%d ", *(a+i));
	printf("\n");}
