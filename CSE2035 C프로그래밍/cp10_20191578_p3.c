#include <stdio.h>

int main(void){
	char sentence[200];
	char word[200];
	fputs("Input string : ", stdout);
	fgets(sentence, sizeof(sentence), stdin);
	int i=0,j=0;
	fputs("- Result -\n", stdout);
	while(sentence[i]!='\0'){
		if((int)sentence[i]==32||(int)sentence[i]=='\n'){
			fputs("\t", stdout);
			fputs(word, stdout);
			fputs("\n", stdout);
			for(int l=0;l<j;l++)
				word[l]=32;
			j=-1;}
		else
			word[j]=sentence[i];
		i++;
		j++;
	}

	return 0;}
