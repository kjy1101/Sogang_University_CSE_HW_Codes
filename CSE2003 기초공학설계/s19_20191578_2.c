#include <stdio.h>

int main(void){
	FILE *test1;
	FILE *test2;
	FILE *test3;
	char filename1[100]={0};
	char filename2[100]={0};
	char c;
	char d;
	int i=0;
	int j=0;
	int k=0;
	int l=0;

	printf("Input first file name: ");
	scanf("%s", filename1);
	printf("Input second file name: ");
	scanf("%s", filename2);

	test1 = fopen(filename1, "r");
	test2 = fopen(filename2, "r");
	test3 = fopen("output", "w");
	
	while((c=fgetc(test1))!=EOF) {
		i++;}

	while((d=fgetc(test2))!=EOF) {
		j++;}


	//fprintf(test3, "Total character(i)=%d\n", i);
	//fprintf(test3, "Total character(j)=%d\n", j);

	if(i<j){
		fprintf(test3, "Total character=%d\n", i);l=i;}
	else {
		fprintf(test3, "Total character=%d\n", j);l=j;}

	fclose(test1);
	fclose(test2);


	test1 = fopen("test1.c", "r");
	test2 = fopen("test2.c", "r");

	while(1){
		while(1) {
			c=fgetc(test1);
			if(c==' '||c=='\n'||c=='\t') {;}
			else if(c==EOF) break;
			else break;}

		while(1) {
			d=fgetc(test2);
			if(d==' '||d=='\n'||d=='\t') {;}
			else if(c==EOF) break;
			else break;}

		if(c==EOF||d==EOF) break;
		if(c==d) k++;
	}

	fprintf(test3, "Same character=%d\n", k);
	fprintf(test3, "%.3f%\n", (((float)k/l)*100));

	fclose(test1);
	fclose(test2);
	fclose(test3);
	return 0;}
