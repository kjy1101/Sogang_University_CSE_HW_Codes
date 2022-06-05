#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
	int number;
	char id[50];
	char pw[50];
	char name[50];
	char address[200];
} customer;

int main(void){
	customer *cus;
	cus=(customer*)malloc(5*sizeof(customer));
	FILE *in = fopen("customer.txt", "r");
	char astring[350];
	char *str;
	int i=0;
	while(i<5){
		fscanf(in, "%d,%[^\n]",&(cus[i].number),astring);

		str=strtok(astring, ",");
		strcpy(cus[i].id, str);

		str=strtok(NULL, ",");
		strcpy(cus[i].pw, str);

		str=strtok(NULL, ",");
		strcpy(cus[i].name, str);

		str=strtok(NULL, ",");
		strcpy(cus[i].address, str);

		i++;
	}
	char ID[50];
	char password[50];
	int flag=0, n=0, index;
	printf("로그인 프로그램\n");
	while(1){
		printf("아이디 : ");
		scanf("%s", ID);
		printf("패스워드 : ");
		scanf("%s", password);
		n++;
		for(int k=0;k<5;k++){
			if(strcmp(cus[k].id, ID)==0&&strcmp(cus[k].pw, password)==0){
				flag=1;
				index=k;}
		}
		if(flag==1){
			printf("=================\n");
			printf("회원번호: %d\n", cus[index].number);
			printf("아이디 : %s\n", cus[index].id);
			printf("패스워드 : %s\n", cus[index].pw);
			printf("이름 : %s\n", cus[index].name);
			printf("주소 : %s\n", cus[index].address);
			break;
		}
		else{
			printf("일치하는 회원이 없습니다.\n");
			if(n==3) break;
		}
	}
	free(cus);
	fclose(in);
	return 0;}
