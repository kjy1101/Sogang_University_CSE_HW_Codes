//tower of hanoi
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hanoi(int total_disk, int n, char A, char B, char C, int *count, FILE *fp);

int main(int argc, char *argv[]){
	clock_t start = clock();
	if(argc!=2){
		printf("usage: ./hw2 number-of-disks\n");
		exit(1);
	}
	
	int k=0; //자릿수
	while(1){
		k++;
		if(argv[1][k]=='\0') break;
	}
	int n=0; //number of disks(calculate by sum)
	int total_disk=0;
	int count=1;
	int temp;
	for(int j=0;j<k;j++){
		temp = argv[1][j]-'0';
		for(int ten=0;ten<k-j-1;ten++){
			temp *= 10;
		}
		n+=temp;
	}
	total_disk=n;

	FILE *fp = fopen("hw2_result.txt", "w");

	hanoi(total_disk, n, 'A', 'B', 'C', &count, fp);
	count--;
	fprintf(fp, "Total number of moves for %d disks: %d\n", total_disk, count);

	clock_t end = clock();
	fprintf(fp, "Running time: %lf seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

	fclose(fp);
	printf("Program Complete. Output saved to hw2_result.txt.\n");
	return 0;
}

void hanoi(int total_disk, int n, char A, char B, char C, int *count, FILE *fp){
	if(n==1){
		//one disk
		fprintf(fp, "MOVE DISK #%d FROM %c TO %c (moves: %d)\n", total_disk-n+1, A, C, *count);
		(*count)++;
	}
	else{
		//many disks
		hanoi(total_disk, n-1, A, C, B, count, fp);
		fprintf(fp, "MOVE DISK #%d FROM %c TO %c (moves: %d)\n", total_disk-n+1, A, C, *count);
		(*count)++;
		hanoi(total_disk, n-1, B, A, C, count, fp);
	}
}
