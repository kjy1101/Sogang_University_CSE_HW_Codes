//naive
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9999999
char string[MAX];
char pat[MAX];
int starting_point[MAX];

void nfind(char *string, char *pat);

int main(void){
	FILE *fp_s = fopen("string.txt", "r");
	if(fp_s==NULL){
		printf("The string file does not exist.\n");
		exit(1);
	}
	fgets(string, MAX, fp_s);
	string[strlen(string)-1]='\0';

	FILE *fp_p = fopen("pattern.txt", "r");
	if(fp_p==NULL){
		printf("The pattern file does not exist.\n");
		exit(1);
	}
	fgets(pat, MAX, fp_p);
	pat[strlen(pat)-1]='\0';
	
	nfind(string, pat);
	printf("Program complete. Result saved to result_naive.txt\n");
	return 0;
}

void nfind(char *string, char *pat){
	int i,j,start=0;
	int lasts = strlen(string)-1;
	int lastp = strlen(pat)-1;
	int endmatch = lastp;
	int count=0;
	starting_point[0] = -1;
	for(i=0;endmatch<=lasts;endmatch++, start++){
		if(string[endmatch]==pat[lastp])
			for(j=0,i=start;j<lastp && string[i]==pat[j];i++, j++);
		if(j==lastp){
			starting_point[count]=start;
			count++;
			j=0;
		} 
	}
	FILE *fp = fopen("result_naive.txt", "w");
	fprintf(fp, "%d\n", count);
	for(int k=0;k<count;k++) fprintf(fp, "%d ", starting_point[k]);
	fprintf(fp, "\n");
}
