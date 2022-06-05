#include <stdio.h>

int main(void){
	char str[100];
	fgets(str, sizeof(str), stdin);
	int char_num=0, i=0;
	while(str[i]!='\n'){
		char_num++; i++;}

	int count=0;
	for(int j=0;j<char_num;j++){
		if((int)str[j]!=32&&(int)str[j+1]==32)
			count++;
		if((int)str[j]!=32&&str[j+1]=='\n')
			count++;
	}
	
	printf("%d\n",count);
	

	return 0;}
