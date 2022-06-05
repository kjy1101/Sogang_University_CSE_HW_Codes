//main함수
#include "Header.h"

int main(void){
	int n;
	int *input_array;
	int count_array[10]={0};
	scanf("%d", &n);
	input_array=(int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		scanf("%d", &input_array[i]);
	}
	
	for(int i=0;i<n;i++){
		int *page_array;
		page_array=(int*)malloc(sizeof(int)*input_array[i]);
		for(int j=0;j<input_array[i];j++){
			page_array[j]=j+1;
		}
		Counting(count_array, page_array, input_array[i]);
		Print(count_array);
		for(int k=0;k<10;k++)
			count_array[k]=0;
	}
return 0;
}
