#include <stdio.h>
void checkWB(char col, int row, char *answer);

int main(void) {
	char col;
	int row;
	char answer;

	scanf("%c%d", &col, &row);
	checkWB(col, row, &answer);
	printf("%c\n", answer);
	return 0;
}

void checkWB(char col, int row, char *answer) {
	if (col == 'a' || col == 'c' || col == 'e' || col == 'g')
		if (row == 1 || row == 3 || row == 5 || row == 7)
			*answer = 'B';
		else
			*answer = 'W';
	else
		if (row == 1 || row == 3 || row == 5 || row == 7)
			*answer = 'W';
		else
			*answer = 'B';
}