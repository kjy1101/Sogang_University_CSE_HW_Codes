#include<stdio.h>

int main(void)
{
	int array[10],Max,Min;

	printf("Input (10 numbers): ");
	for(int i=0;i<10;i++)
	{
		scanf("%d",&array[i]);
	}
	Max=Min=array[0];

	for(int i=0;i<5;i++)
	{
		int temp=array[i];

		array[i]=array[9-i];
		array[9-i]=temp;
	}

	for(int i=0;i<10;i++)
	{
		if(array[i]>Max)
		{
			Max=array[i];
		}
		if(array[i]<Min)
		{
			Min=array[i];
		}

		printf("%d ",array[i]);
	}

	printf("\nMax: %d, Min: %d\n",Max,Min);

	return 0;
}

