#include <stdio.h>

int main(void){
	FILE *input;
	FILE *output;

	input = fopen("student.txt", "r");
	output = fopen("output33.txt", "w");

	char name[6]={0};
	float mid=0, fin=0;
	int count=0;
	float total=0, average=0;
	int res;

	if (input == NULL){
		printf("Cannot read file.\n");
		return 1;}

	if (output == NULL){
		printf("Canno write file.\n");
		return 1;}


	while(1){
		res = fscanf(input, "%s %f %f", name, &mid, &fin);
		if (res == EOF) break;

		total += (mid + fin);
		count += 2;}

	average = total / count;

	fclose(input);
	input = fopen("student.txt", "r");

	fprintf(output, "student             average grade\n");

	while(1){
		res = fscanf(input, "%s %f %f", name, &mid, &fin);
		if (res == EOF)  break;

		float ind_avg=0;
		ind_avg = (mid + fin)/2;

		if (ind_avg >= average)
			fprintf(output, "%-20s %.2f   %c\n", name, ind_avg, 'p');
		else
			fprintf(output, "%-20s %.2f   %c\n", name, ind_avg, 'f');}
	fprintf(output, "total avg : %.2f\n", average);

	fclose(input);
	fclose(output);

	return 0;}
