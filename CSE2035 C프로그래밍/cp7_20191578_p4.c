#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int swap(int *a, int *b);
int bubble(int *a, int n);
int* merge(int *ary1, int size1, int *ary2, int size2, int *ary3, int size3);
int min(int a, int b, int c);

int main(void){
	int *ary1, *ary2, *ary3, *result_array;
	int size1=3, size2=4, size3=5;
	ary1=(int*)calloc(size1,sizeof(int));
	ary2=(int*)calloc(size2,sizeof(int));
	ary3=(int*)calloc(size3,sizeof(int));
	result_array=(int*)calloc(size1+size2+size3,sizeof(int));
	printf("Input 12 integer: ");
	for(int i=0;i<size1;i++)
		scanf("%d", &ary1[i]);
	for(int i=0;i<size2;i++)
		scanf("%d", &ary2[i]);
	for(int i=0;i<size3;i++)
		scanf("%d", &ary3[i]);
	printf("Array 1       : ");
	for(int i=0;i<size1;i++)
		printf("%d ", ary1[i]);
	printf("\n");
	printf("Array 2       : ");
	for(int i=0;i<size2;i++)
		printf("%d ", ary2[i]);
	printf("\n");
	printf("Array 3       : ");
	for(int i=0;i<size3;i++)
		printf("%d ", ary3[i]);
	printf("\n");

	bubble(ary1, size1);
	bubble(ary2, size2);
	bubble(ary3, size3);

	result_array=merge(ary1, size1, ary2, size2, ary3, size3);
	printf("result Array  : ");
	for(int i=0;i<size1+size2+size3;i++)
		printf("%d ", result_array[i]);
	printf("\n");

	free(ary1);
	free(ary2);
	free(ary3);
	free(result_array);
	return 0;}

int swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;}

int bubble(int *a, int n){
	for(int i=n-1;i>0;i--){
		for(int j=0;j<i;j++){
			if(*(a+j)>*(a+j+1))
				swap(a+j, a+j+1);}}}

int* merge(int *ary1, int size1, int *ary2, int size2, int *ary3, int size3){
	int *result;
	result=(int*)calloc(size1+size2+size3, sizeof(int));
	int i=0,j=0,k=0,l=0,m;
	while(1){
		m=min(ary1[i], ary2[j], ary3[k]);
		if(m==ary1[i]) {
			i++;
			if(i>=size1)
				ary1[i]=INT_MAX;}
		else if(m==ary2[j]) {
			j++;
			if(j>=size2)
				ary2[j]=INT_MAX;}
		else if(m==ary3[k]) {
			k++;
			if(k>=size3)
				ary3[k]=INT_MAX;}
		result[l]=m;
		l++;
		if(l==12) break;
		}
	return result;
}

int min(int a,int b,int c){
	int min;
	if(a<b)
		min=a;
	else
		min=b;
	if(c<min)
		min=c;
	return min;}
