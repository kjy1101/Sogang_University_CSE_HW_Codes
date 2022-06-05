#include <stdio.h>
float check(float c1, float c2, float c3, float c4);

int main(void) {
	float c1, c2, c3, c4;
	scanf("%f %f %f %f", &c1, &c2, &c3, &c4);
	printf("%.1f\n", check(c1, c2, c3, c4));
}

float check(float c1, float c2, float c3, float c4) {
	float distance;
	if ((c4 - c2) < (c2 - c1))
		distance = c4 - c2;
	if ((c3 - c1) < (c4 - c3))
		distance = c3 - c1;
	if ((c2 - c1) < (c3 - c2) && (c4 - c3) < (c3 - c2))
		distance = c2 - c1 + c4 - c3;
	return distance;
}