#include <stdio.h>

float weightSum(int *five_ago, int *four_ago, int *three_ago, int *two_ago, int *one_ago);
void printBySection(float weight_sum);

int main(void)
{
	int five_ago, four_ago, three_ago, two_ago, one_ago;
	scanf("%d %d %d %d %d", &five_ago, &four_ago, &three_ago, &two_ago, &one_ago);
	float weight_sum;
	weight_sum = weightSum(&five_ago, &four_ago, &three_ago, &two_ago, &one_ago);
	printBySection(weight_sum);

	return 0;
}

float weightSum(int *five_ago, int*four_ago, int*three_ago, int *two_ago, int*one_ago)
{
	float total;
	total = *five_ago*0.04 + *four_ago*0.06 + *three_ago*0.15 + *two_ago*0.25 + *one_ago*0.5;
	return total;
}

void printBySection(float weight_sum)
{
	if (weight_sum >= 0 && weight_sum < 30)
		printf("%.2f good\n", weight_sum);
	if (weight_sum >= 30 && weight_sum < 80)
		printf("%.2f normal\n", weight_sum);
	if (weight_sum >= 80 && weight_sum < 150)
		printf("%.2f bad\n", weight_sum);
	if (weight_sum >= 150)
		printf("%.2f very bad\n", weight_sum);
}
