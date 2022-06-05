#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int num;
	char name[20];
	char type1[30];
	char type2[30];
}dex;

int main(void){
	int input,number;
	char type[30], Name[30];
	char astring[30];

	printf("1. National Number\n");
	printf("2. Name\n");
	printf("3. Type\n");
	printf("Input = ");
	scanf("%d", &input);

	dex *pmon;
	pmon=(dex*)malloc(151*sizeof(dex));

	int i=0;
	FILE *in = fopen("pokedex.txt", "r");
	while(!feof(in)){
		fscanf(in, "%d %s %s\n", &pmon[i].num, &pmon[i].name, &astring);
		//strcpy(pmon[i].type2, pmon[i].type1);
		char *str = strchr(astring, ',');
		if ( str == NULL ) {
			strcpy(pmon[i].type1, astring);
			pmon[i].type2[0] = 0;
		}
		else {
			strcpy(pmon[i].type2, str+1);
			*str = 0;
			strcpy(pmon[i].type1, astring);
		}
	i++;}
	
	
/*	for(int i=0;i<50;i++){
		printf("num: %d\nname: %s\ntype1: %s\ntype2: %s\n\n", pmon[i].num, pmon[i].name, pmon[i].type1, pmon[i].type2);}*/


	if(input==1){
		printf("Search by National Number = ");
		scanf("%d", &number);
		number--;
		printf("Result--------------------\n\n");
		printf("National Number : %d\n", pmon[number].num);
		printf("Name : %s\n", pmon[number].name);
		if(pmon[number].type2[0] == 0)
			printf("Type : %s\n\n", pmon[number].type1);
		else{
		printf("Type1 : %s\n", pmon[number].type1);
		printf("Type2 : %s\n\n", pmon[number].type2);}
		printf("---------------------------\n");
	}
	else if(input==2){
		printf("Search by Name : ");
		scanf("%s", Name);
		printf("Result--------------------\n\n");
		for(int i=0;i<151;i++){
			if(strstr(pmon[i].name, Name)!=NULL){
				printf("National Number : %d\n", pmon[i].num);
				printf("Name : %s\n", pmon[i].name);
				
			if(pmon[i].type2[0] == 0)
				printf("Type : %s\n\n", pmon[i].type1);
			else{
				printf("Type1 : %s\n", pmon[i].type1);
				printf("Type2 : %s\n\n", pmon[i].type2);}

		}}
	
		printf("---------------------------\n");
	}
	else if(input==3){
		printf("Search by Type : ");
		scanf("%s", type);
		printf("Result--------------------\n\n");
		for(int i=0;i<151;i++){
			if(strcmp(pmon[i].type1, type)==0||strcmp(pmon[i].type2, type)==0){
				printf("National Number : %d\n", pmon[i].num);
				printf("Name : %s\n", pmon[i].name);
		if(pmon[i].type2[0] == 0)
			printf("Type : %s\n\n", pmon[i].type1);
		else{
		printf("Type1 : %s\n", pmon[i].type1);
		printf("Type2 : %s\n\n", pmon[i].type2);}
			}}
		printf("---------------------------\n");
	}
	else
		return;
	return 0;}
