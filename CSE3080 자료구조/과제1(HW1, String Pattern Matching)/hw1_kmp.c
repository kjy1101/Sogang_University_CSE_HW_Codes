//kmp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9999999

void pmatch(char*, char*);
void fail(char*);

int failure[MAX];
char string[MAX];
char pat[MAX];
int starting_point[MAX];

void main(){
	FILE *fp_s = fopen("string.txt", "r");
	if(fp_s==NULL){
		printf("The string file does not exist.\n");
		exit(1);
	}
	fgets(string, MAX, fp_s);
	string[strlen(string)-1] = '\0';

	FILE *fp_p = fopen("pattern.txt", "r");
	if(fp_p==NULL){
		printf("The pattern file does not exist.\n");
		exit(1);
	}
	fgets(pat, MAX, fp_p);
	pat[strlen(pat)-1] = '\0';

	fail(pat);

	pmatch(string, pat);
	printf("Program complete. Result saved to result_kmp.txt\n");
}

void fail(char *pat){
	int i,j,n = strlen(pat);
	failure[0] = -1;
	for(j=1;j<n;j++){
		i = failure[j-1];
		while((pat[j] != pat[i+1]) && (i >= 0)) i = failure[i];
		if(pat[j] == pat[i+1]) failure[j] = i+1;
		else failure[j] = -1;
	}
}

void pmatch(char *string, char *pat){
	int i=0, j=0;
	int count=0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	starting_point[0] = -1;
	while (i < lens && j < lenp){
		if(string[i] == pat[j]){i++; j++;}
		else if(j == 0) i++;
		else j = failure[j-1] + 1;
		if(j==lenp){
				starting_point[count] = i - lenp;
				j=0;
				i = i - lenp + 1;
				count++;
		}
	}
	FILE *fp = fopen("result_kmp.txt", "w");
	fprintf(fp, "%d\n", count);
	for(int k=0;k<count;k++) fprintf(fp, "%d ", starting_point[k]);
	fprintf(fp, "\n");
}
