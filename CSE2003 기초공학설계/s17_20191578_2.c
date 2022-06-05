#include <stdio.h>

int main(void){
	int numbers[10], i;
	printf("Input (10 numbers): ");
	for(i=0;i<10;i++){
		scanf("%d", &numbers[i]);}

	for(i=0;i<5;i++){
		int temp;
		temp = numbers[i];
		numbers[i] = numbers[9-i];
		numbers[9-i] = temp;}

	for(i=0;i<10;i++){
		printf("%d ", numbers[i]);}
	printf("\n");

	int max;
	max = numbers[0];
	for(i=1;i<10;i++){
		if (numbers[i] > max)
			max = numbers[i];}

	int min;
	min = numbers[0];
	for(i=1;i<10;i++){
		if (numbers[i] < min)
			min = numbers[i];}

	printf("Max: %d, Min: %d\n", max, min);

	return 0;}
