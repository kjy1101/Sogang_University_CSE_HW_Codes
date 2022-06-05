#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char* string1, * string2;
	string1 = (char*)malloc(20 * sizeof(char));
	string2 = (char*)malloc(20 * sizeof(char));
	gets(string1);
	gets(string2);
	int count = 0;
	for (int i = 0; i < strlen(string1); i++) {
		if (*(string1 + i) >= 65 && *(string1 + i) <= 90)
			* (string1 + i) += 32;
	}
	for (int i = 0; i < strlen(string2); i++) {
		if (*(string2 + i) >= 65 && *(string2 + i) <= 90)
			* (string2 + i) += 32;
	}
	if (strlen(string1) == strlen(string2)) {
		for (int i = 0; i < strlen(string1); i++) {
			if (*(string1 + i) == *(string2 + i))
				count++;
		}
		if (count == strlen(string1))
			printf("Equal\n");
		else
			printf("Not equal\n");
	}
	else
		printf("Not equal\n");

	free(string1);
	free(string2);
	return 0;
}