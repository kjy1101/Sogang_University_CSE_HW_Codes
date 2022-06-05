#include <stdio.h>
int merge(int arrayA[5], int arrayB[5], int arrayMerge[10]);

int main(void){
	int arrayA[5]={0};
	int arrayB[5]={0};
	int arrayMerge[10]={0};

	printf("Input arrayA: ");
	for(int i=0;i<5;i++){
		scanf("%d", &arrayA[i]);}

	printf("Input arrayB: ");
	for(int i=0;i<5;i++){
		scanf("%d", &arrayB[i]);}

	merge(arrayA, arrayB, arrayMerge);
	printf("Merged array: ");
	for (int i=0;i<10;i++){
		printf("%d ", arrayMerge[i]);}

	printf("\n");

	return 0;}



int merge(int arrayA[5], int arrayB[5], int arrayMerge[10]){
	int i=0, j=0, k=0;
	for (int i=0;i<10;i++){
		if (j<5 && k<5){
			if (arrayA[j] >= arrayB[k]){
				arrayMerge[i] = arrayB[k];
				k++;}

			else{
				arrayMerge[i] = arrayA[j];
				j++;}}

//	printf("%d %d\n", j, k);

		else if (j<5){
			arrayMerge[i] = arrayA[j];
			j++;}
		else{
			arrayMerge[i] = arrayB[k];
			k++;}}
	return 0;}
