#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n;
	char** matrix;
	scanf("%d", &n);
	matrix = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) {
		*(matrix + i) = (char*)malloc(20 * sizeof(char));
	}
	for (int i = 0; i < n; i++) {
		scanf("%s", *(matrix + i));
	}

	printf("-Lexicographic Order-\n");

	/*for (int i = 0; i < n; i++) {
		for (int j = strlen(*(matrix + i)) - 1; j > 0; j--) {
			for (int k = 0; k < j; k++) {
				if (*(*(matrix + i) + k) > *(*(matrix + i) + k + 1)) {
					char temp;
					temp = *(*(matrix + i) + k);
					*(*(matrix + i) + k) = *(*(matrix + i) + k + 1);
					*(*(matrix + i) + k + 1) = temp;
				}
			}
		}
	}*/

	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (strcmp(*(matrix + j), *(matrix + j + 1)) == 1) {
				char* temp;
				temp = (char*)malloc(20 * sizeof(char));
				strcpy(temp, *(matrix + j));
				strcpy(*(matrix + j), *(matrix + j + 1));
				strcpy(*(matrix + j + 1), temp);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		printf("%s\n", *(matrix + i));
	}
	free(matrix);
	return 0;
}