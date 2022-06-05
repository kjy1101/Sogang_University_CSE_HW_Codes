#include <stdio.h>
#include <stdlib.h>

int main(void){
	char text[500];
	char word[100];
	char *new_word;
	char *temp;
	fputs("Text : ", stdout);
	fgets(text, sizeof(text), stdin);
	fputs("Word : ", stdout);
	fgets(word, sizeof(text), stdin);

	int text_count=0,word_count=0;
	int i=0;
	while(text[i]!='\n'){
		text_count++;i++;}
	i=0;
	while(word[i]!='\n'){
		word_count++;i++;}

	word_count+=2;
	new_word=(char*)malloc(word_count*sizeof(char));
	new_word[0]=32;
	new_word[word_count-1]=32;
	int k=0;
	for(int j=1;j<word_count-1;j++){
		new_word[j]=word[k];
		k++;}

	int count=0, text_idx=0, word_idx=0,flag=0;
	//맨 첫 단어가 같을 때
	for(int a=0;a<word_count-2;a++){
		if(text[a]==word[a]) flag++;}
	if(flag==word_count-2) count++;
	text_idx++;
	//중간
	while(text[text_idx]!='\n'){
		for(int l=text_idx;l<text_idx+word_count;l++){
			if(text[l]==new_word[word_idx]){
				flag++;word_idx++;}}
		if(flag==word_count) count++;
		flag=0;
		word_idx=0;
		text_idx++;
	}
	//제일 마지막
	int idx=0;
	for(int a=text_idx-word_count+2;a<text_idx;a++){
		if(text[a]==word[idx]) flag++; idx++;}
	if(flag==word_count-2) count++;

	//word 문자열 맨 마지막에 '\n' 삭제하기
	word_count-=2;
	temp=(char*)malloc(word_count*sizeof(char));
	for(int c=0;c<word_count;c++)
		temp[c]=new_word[c+1];


	printf("Number of '%s' : %d\n",temp,count);
	
	free(new_word);
	free(temp);

	return 0;}
