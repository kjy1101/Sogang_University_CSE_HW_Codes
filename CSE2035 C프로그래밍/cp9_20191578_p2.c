#include <stdio.h>
#include <stdlib.h>
void function(char* array, int length);
int number(char* num_array, int len);
int power(int a, int b);
void print(char *new_array, int number);

int main(void){
	char *string, *newarray;
	string=(char*)malloc(20*sizeof(char));
	newarray=(char*)malloc(20*sizeof(char));
	scanf("%s", string);
	
	int j=0;
	for(int i=0;i<20;i++){
		*(newarray+j)=*(string+i);
		j++;
		if(*(string+i)<65&&*(string+i+1)>=65){
			function(newarray,j);
			j=0;
			}
		if(*(string+i)=='\0'){
			function(newarray,j-1);
			break;}}
	printf("\n");

	free(string);
	free(newarray);
		
	return 0;}

void function(char* array, int length){
//	printf("original: %s	%d\n", array, length);
	int l=0;
	char *num_array,*new_array;
	num_array=(char*)malloc(20*sizeof(char));
	for(int i=0;i<length;i++){
		if(*(array+i)<65){
			*(num_array+l)=*(array+i);
			l++;}}
	int num;
	num=number(num_array,l);
	new_array=(char*)malloc((length-l)*sizeof(char));
	for(int i=0;i<length-l;i++){
		*(new_array+i)=*(array+i);}
//	printf("character: %s\n",new_array);
//	printf("integer number: %d\n\n",num);

	print(new_array,num);

	free(num_array);
	free(new_array);
}

int number(char* num_array, int len){
	int number=0;
	int *reverse;
	reverse=(int*)malloc(len*sizeof(int));
	for(int i=0;i<len;i++)
		*(reverse+i)=*(num_array+len-i-1)-'0';
	for(int i=0;i<len;i++){
		*(reverse+i)*=power(10,i);
		number+=*(reverse+i);}
	free(reverse);
	return number;
}

int power(int a, int b){
	//a가 밑, b가 지수(a의 b승)
	int result=1;
	if(b==0) return 1;
	else{
	for(int i=0;i<b;i++)
		result*=a;
	return result;}}

void print(char *new_array, int number){
	for(int i=0;i<number;i++)
		printf("%s",new_array);
}
