#include <stdio.h>
#include <string.h>

typedef struct{
	char name[20];
	char subject[20];
	int score;
} STUDENT;

typedef union
{
	char name[20];
	char subject[20];
	int score;
} Student;

int main(void){
	STUDENT student;
	Student stu;
	scanf("%s %s %d", student.name, student.subject, &(student.score));
	//첫번째 출력
	strcpy(stu.name, student.name);
	strcpy(stu.subject, student.subject);
	stu.score=student.score;
	printf("Name		: %s\n", stu.name);
	printf("Subject		: %s\n", stu.subject);
	printf("Score		: %d\n", stu.score);

	//두번째 출력
	strcpy(stu.name, student.name);
	printf("Name		: %s\n", stu.name);
	strcpy(stu.subject, student.subject);
	printf("Subject		: %s\n", stu.subject);
	stu.score=student.score;
	printf("Score		: %d\n", stu.score);

	//두 출력결과가 다른 이유
	//공용체는 메모리를 공유하기 때문에 하나를 사용하면 다른 데이터는 사라진다.
	//첫번째 출력은 앞에서 저장한 name과 subject는 의미없는 값이 되고, 마지막으로 넣은 score만 제대로 출력된다.
	//두번째 출력은 의미없는 값이 되어버리기 전에 바로바로 출력하는 것이므로, 모두 제대로 출력된다.

	return 0;}
