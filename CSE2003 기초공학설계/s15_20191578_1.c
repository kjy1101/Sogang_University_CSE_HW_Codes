#include <stdio.h>
int main(void){
	int i, n, x, total=0, failure=0;
	printf("Number of class: ");
	scanf("%d", &n);
	printf("Cutline: ");
	scanf("%d", &x);
	while ( i < n){
		int score;
		printf("Input score #%d: ", i);
		scanf("%d", &score);
		total += score;
		if (score < x){
			failure += 1;}
		i++;
	}
	printf("Average score: %.2f\n", ((float)total) / n);
	printf("Number of failures: %d\n", failure);
	return 0;
}
