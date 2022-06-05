#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n;
	char *array;
	scanf("%d", &n);
	array=(char*)malloc(n*sizeof(char));
	scanf("%s", array);
	int count=0;
	int i=0;
	while(array[i]!='\0'){
		count++;
		i++;}
	array=(char*)realloc(array, count*sizeof(char));
	for(int i=0;i<n;i++)
		printf("%c", array[i]);
	printf("\n");
	for(int i=n;i<count;i++)
		printf("%c", array[i]);
	printf("\n");
	free(array);
	return 0;}
