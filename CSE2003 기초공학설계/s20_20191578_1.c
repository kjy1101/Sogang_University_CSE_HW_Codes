#include <stdio.h>

int main(void){
	FILE *input;
	FILE *output;

	input = fopen("input32.txt", "r");
	output= fopen("output32.txt", "w");

	float n1=0, n2=0, n3=0;
	char math, equal;
	float result=0;
	int res;

	if (input == NULL){
		printf("Cannot read file.\n");
		return 1;}

	if (output == NULL){
		printf("Cannot write file.\n");
		return 1;}

	while(1){
		res = fscanf(input, "%f %c %f %c %f", &n1, &math, &n2, &equal, &n3);
		if (res == EOF) break;

		switch (math){
			case '+': result = n1 + n2;
					  break;
			case '-': result = n1 - n2;
					  break;
			case '*': result = n1 * n2;
					  break;
			case '/': result = n1 / n2;
					  break;
			case '%': result = (int)n1 % (int)n2;
					  break;
		}

		if (result == n3)
			fprintf(output, "%.2f %c %.2f %c %.2f correct\n", n1, math, n2, equal, n3);
		else
			fprintf(output, "%.2f %c %.2f %c %.2f incorrect\n", n1, math, n2, equal, n3);}

	return 0;}
