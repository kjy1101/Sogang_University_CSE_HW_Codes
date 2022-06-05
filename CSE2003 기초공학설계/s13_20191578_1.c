#include <stdio.h>

int main(void){
int year;

printf("Enter the year to be tested: ");
scanf("%d", &year);

int remain1, remain2, remain3;
remain1 = year % 4;
remain2 = year % 100;
remain3 = year % 400;

if ((remain1 == 0) && (remain2 != 0))
	printf("It is a leap year.\n");
else if (remain3 == 0)
	printf("It is a leap year.\n");
else
	{printf("It is not a leap year.\n");
	printf("%d is a leap year.\n", year - remain1);}
return 0;}
