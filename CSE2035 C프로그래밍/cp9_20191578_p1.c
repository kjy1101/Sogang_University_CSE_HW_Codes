#include <stdio.h>
#include <stdlib.h>

int main(void){
	char *word, *reverse;
	word=(char*)calloc(101,sizeof(char));
	reverse=(char*)calloc(101,sizeof(char));
	scanf("%s", word);
	int i=0, length;
	while(1){
		if(*(word+i)=='\0'){
			length=i;
			break;}
		i++;}
	for(int j=0;j<length;j++){
		*(reverse+j)=*(word+length-j-1);}

	int flag=0;
	for(int j=0;j<length;j++){
		if(*(word+j)!=*(reverse+j))
			flag=1;}
	if(flag==1) printf("Not palindrome.\n");
	else printf("Palindrome.\n");

	free(word);
	free(reverse);

	return 0;}
