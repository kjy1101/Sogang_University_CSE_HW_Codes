#include <stdio.h>

float avgFunc(float a1, float a2, float a3);
char gradeFunc(float avg);

int main(void){
	float a1, a2, a3;
	printf("Input: ");
	scanf("%f %f %f", &a1, &a2, &a3);
	gradeFunc(avgFunc(a1, a2, a3));
	return 0;
}

float avgFunc(float a1, float a2, float a3){
	float avg;
	avg = (a1 + a2 + a3) / 3;
	return avg;
}

char gradeFunc(float avg){
	int grade;
	if (avg >= 50){
		if (avg < 70)
			grade = 68;
		else
			if (avg < 80)
				grade = 67;
			else
				if (avg < 90)
					grade = 66;
				else
					grade = 65;}
	else
		grade = 70;
	printf("Grade: %c\n", grade);
}
