#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union utemp{
	int i;
	float f;
	double d;
};

typedef struct{
	int type;		//1:int, 2:float, 3:double
	char name[20];	//변수 타입
	union utemp u;	//입력받은 수
} stemp;

void power(stemp *s);

int main(void){
	int num_iter=0;
	stemp *s;
	printf("Number of Iterations : ");
	scanf("%d", &num_iter);
	s=(stemp*)malloc(sizeof(stemp)*num_iter);

	for(int i=0;i<num_iter;i++){
		printf("Type [1 for int, 2 for float, 3 for double] : ");
		scanf("%d", &(s[i].type));
		switch (s[i].type){
			case 1:
				printf("Enter an integer value : ");
				scanf("%d", &(s[i].u.i));
				strcpy(s[i].name, "integer");
				power(&(s[i]));
				break;
			case 2: 
				printf("Enter a float value : ");
				scanf("%f", &(s[i].u.f));
				strcpy(s[i].name, "float");
				power(&(s[i]));
				break;
			case 3:
				printf("Enter a double value : ");
				scanf("%lf", &(s[i].u.d));
				strcpy(s[i].name, "double");
				power(&(s[i]));
				break;
		}
	}

	printf("--------Result--------\n");
	for(int j=0;j<num_iter;j++){
		switch(s[j].type){
			case 1:
				printf("%-10s : %d\n", s[j].name, s[j].u.i);
				break;
			case 2: 
				printf("%-10s : %.4f\n", s[j].name, s[j].u.f);
				break;
			case 3:
				printf("%-10s : %.4lf\n", s[j].name, s[j].u.d);
				break;
		}
	}

	return 0;}

void power(stemp *s){
	switch (s->type){
		case 1:
			(s->u.i)*=(s->u.i);
			break;
		case 2:
			(s->u.f)*=(s->u.f);
			break;
		case 3:
			(s->u.d)*=(s->u.d);
			break;
	}
}
