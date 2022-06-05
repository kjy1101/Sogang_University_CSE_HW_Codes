#include <stdio.h>
#include <stdlib.h>

typedef struct __SUBJECT__{
	char number[8]; //과목번호
	int credit; //학점
	double grade; //성적
} subject;

typedef struct __STUDENT__{
	int id; //학번
	int number_of_course; //수강 과목 수
	subject *courses;
} student;

typedef struct {
	int ID;
	double cgpa;
} print;

double calcCGPA(student s);

int main(void){
	int stu_n;
	double cgpa;
	scanf("%d", &stu_n);
	student *stu;
	print *pri;
	stu=(student*)malloc(sizeof(student)*stu_n);
	pri=(print*)malloc(sizeof(print)*stu_n);
	for(int i=0;i<stu_n;i++){
		scanf("%d %d", &(stu[i].id),&(stu[i].number_of_course));
		stu[i].courses=(subject*)malloc(sizeof(subject)*stu[i].number_of_course);
		cgpa=calcCGPA(stu[i]);
		pri[i].ID=stu[i].id;
		pri[i].cgpa=cgpa;
//		printf("=======%d's CGPA is %lf=======\n", stu[i].id, cgpa);
	}

	printf("==========\n");
	for(int i=0;i<stu_n;i++){
		printf("%d / %lf\n", pri[i].ID, pri[i].cgpa);
	}

	return 0;}

double calcCGPA(student s){
	double CGPA=0;
	double sum_cre=0;
	for(int i=0;i<s.number_of_course;i++){
		scanf("%s %d %lf", s.courses[i].number, &(s.courses[i].credit), &(s.courses[i].grade));
		CGPA+=s.courses[i].credit*s.courses[i].grade;
		sum_cre+=s.courses[i].credit;
	}
	CGPA/=sum_cre;
	return CGPA;
}
