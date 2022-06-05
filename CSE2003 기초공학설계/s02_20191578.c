#include <stdio.h>

/* 20191578 Kim Jae Yeon */

int main(void)
{
	char ch;	/* ch : identifier character */
	int integer;	/* integer : identifier integer */
	float real;	/* real : identifier float */

	printf("Input one character, one integer, one real number : ");
	scanf("%c %d %f", &ch, &integer, &real);
	/* You can input value by scanf().
	   There should be '&' infront of the name of identifier.
	   If you are going to input more than 2 values,
		 each value should be divided by space. */
	printf("%c %d %f\n", ch, integer, real);
	/* printf() outputs value.
	   You have to input different characters such as %c, %d, %f
		according to the type of value. */

	return 0;
}
