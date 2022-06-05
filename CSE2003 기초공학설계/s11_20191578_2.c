#include <stdio.h>

void caesar(char *alphabet, int key);
int main(void) {
	char a, b, c;
	int key;
	scanf("%d %c%c%c", &key, &a, &b, &c);
	caesar(&a, key);
	caesar(&b, key);
	caesar(&c, key);
	printf("%c%c%c\n", a, b, c);
	return 0;
}

void caesar(char *alphabet, int key) {
	int r = key % 26;
	int total = *alphabet + r;
	if (total >= 97 && total <= 122)
		*alphabet += r;
	if (total > 122)
		*alphabet = *alphabet + r - 26;
	if (total < 97)
		*alphabet = *alphabet + r + 26;
}
