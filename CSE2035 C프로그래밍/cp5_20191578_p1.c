#include <stdio.h>
#include <stdlib.h>
char *triple_concatenate(char *str1, char *str2, char *str3);
int string_length(char *str);

int main(void){
	int size1, size2, size3;
	char *str1, *str2, *str3;
	char *result;

	printf("Input size of str1 : ");
	scanf("%d", &size1);
	str1=malloc(size1*sizeof(char));
	printf("Input str1 : ");
	scanf("%s", str1);
	
	printf("Input size of str2 : ");
	scanf("%d", &size2);
	str2=malloc(size2*sizeof(char));
	printf("Input str2 : ");
	scanf("%s", str2);

	printf("Input size of str3 : ");
	scanf("%d", &size3);
	str3=malloc(size3*sizeof(char));
	printf("Input str3 : ");
	scanf("%s", str3);

	printf("\n");

	printf("str1     : %s\n", str1);
	printf("str2     : %s\n", str2);
	printf("str3     : %s\n", str3);

	result=triple_concatenate(str1, str2, str3);
	printf("result   : %s\n", result);

	free(str1);
	free(str2);
	free(str3);
	free(result);

	return 0;}

char *triple_concatenate(char *str1, char *str2, char *str3){
	int length1=string_length(str1);
	int length2=string_length(str2);
	int length3=string_length(str3);
	char *result=malloc(length1*sizeof(char)+length2*sizeof(char)+length3*sizeof(char));
	for(int i=0;i<length1;i++)
		result[i]=str1[i];
	for(int j=0;j<length2;j++)
		result[length1+j]=str2[j];
	for(int l=0;l<length3;l++)
		result[length1+length2+l]=str3[l];
	return result;
}

int string_length(char *str){
	int i=0;
	while(str[i]!='\0'){
		i++;}
	return i;}
