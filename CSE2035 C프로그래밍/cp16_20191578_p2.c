#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER 10
#define MAX_POKE_CNT 6

typedef struct{
	int num;
	char name[20];
	int level;
	char type1[60];//30
	char type2[60];//30

	char sk1[100];//20
	char sk2[100];
	char sk3[100];
	char sk4[100];
} dex;

typedef struct{
	int inx;
	char name[10];
	char region[10];
	dex poke[6];
} user;

int main(void){
	user *master;
	int number_user = 0;
	char d_name[10];
	char d_region[10];
	int d_num;
	char d_pname[20];
	int d_level;
	char d_type[60];
	char d_sk[100];
	char *pch;
	char *psk;

	master=(user*)calloc(MAX_USER, sizeof(user));

	FILE *in = fopen("user.txt", "r");
	fscanf(in, "%s %s %d %s %d %s %s", d_name, d_region, &d_num, d_pname, &d_level, d_type, d_sk);

	strcpy(master[0].name, d_name);
	strcpy(master[0].region, d_region);
	master[0].poke[0].num = d_num;
	strcpy(master[0].poke[0].name, d_pname);
	master[0].poke[0].level = d_level;

	pch = strtok(d_type, ",");
	strcpy(master[0].poke[0].type1, pch);
	pch = strtok(NULL, ",");	
	if ( pch != NULL ) {
		strcpy(master[0].poke[0].type2, pch);
	}


	psk = strtok(d_sk, ",");
	strcpy(master[0].poke[0].sk1, psk);
	
	psk = strtok(NULL, ",");
	strcpy(master[0].poke[0].sk2, psk);

	psk = strtok(NULL, ",");
	strcpy(master[0].poke[0].sk3, psk);

	psk = strtok(NULL, ",");
	strcpy(master[0].poke[0].sk4, psk);

	number_user++;	

	int k = 0;
	while(!feof(in)){
		fscanf(in, "%s %s %d %s %d %s %s", d_name, d_region, &d_num, d_pname, &d_level, d_type, d_sk);
//		printf("\nnumber_user= %d, %s %s %d %s %d %s %s", number_user, d_name, d_region, d_num, d_pname, d_level, d_type, d_sk);

		for( k = 0; k < number_user; k++) {

			if(strcmp(d_name, master[k].name)==0){
				for ( int j = 0; j < MAX_POKE_CNT; j++ ) {
					if ( master[k].poke[j].name[0] == 0 ) {
						strcpy(master[k].poke[j].name, d_pname);
						pch = strtok(d_type, ",");
						strcpy(master[k].poke[j].type1, pch);
						pch = strtok(NULL, ",");	
						if ( pch != NULL ) {
							strcpy(master[k].poke[j].type2, pch);
						}

						psk = strtok(d_sk, ",");
						strcpy(master[k].poke[j].sk1, psk);
	
						psk = strtok(NULL, ",");
						strcpy(master[k].poke[j].sk2, psk);

						psk = strtok(NULL, ",");
						strcpy(master[k].poke[j].sk3, psk);

						psk = strtok(NULL, ",");
						strcpy(master[k].poke[j].sk4, psk);


						master[k].poke[j].num = d_num;
						master[k].poke[j].level = d_level;
						break;
					}
				}
				break;
			}
		}

		if ( k == number_user ) {
			strcpy(master[number_user].name, d_name);
			strcpy(master[number_user].region, d_region);
			master[number_user].poke[0].num = d_num;
			strcpy(master[number_user].poke[0].name, d_pname);
			master[number_user].poke[0].level = d_level;
			pch = strtok(d_type, ",");
			strcpy(master[number_user].poke[0].type1, pch);
			pch = strtok(NULL, ",");	
			if ( pch != NULL ) {
				strcpy(master[number_user].poke[0].type2, pch);
			}

			psk = strtok(d_sk, ",");
			strcpy(master[number_user].poke[0].sk1, psk);
	
			psk = strtok(NULL, ",");
			strcpy(master[number_user].poke[0].sk2, psk);

			psk = strtok(NULL, ",");
			strcpy(master[number_user].poke[0].sk3, psk);

			psk = strtok(NULL, ",");
			strcpy(master[number_user].poke[0].sk4, psk);

			number_user++;	
		}
	}

	fclose(in);

	printf("Number of Users = %d\n\n", number_user);
	for( int a=0;a<number_user;a++) {
		printf("[Name] %s(%s)\n", master[a].name, master[a].region);	
		printf(" [Pokemon]\n");
		for ( int b=0;b<6;b++) {
			printf("   [Name]%s(%d)\n", master[a].poke[b].name, master[a].poke[b].num);
			printf("   [Level]%d\n", master[a].poke[b].level);
			if ( master[a].poke[b].type2[0] == 0 ) {
				printf("   [Type]%s\n", master[a].poke[b].type1);
			}
			else {
				printf("   [Type1]%s\n", master[a].poke[b].type1);
				printf("   [Type2]%s\n", master[a].poke[b].type2);
			}
			printf("   [Skill1]%s\n", master[a].poke[b].sk1);
			printf("   [Skill2]%s\n", master[a].poke[b].sk2);
			printf("   [Skill3]%s\n", master[a].poke[b].sk3);
			printf("   [Skill4]%s\n", master[a].poke[b].sk4);
			printf("\n");
		}

	}

	return 0;}
