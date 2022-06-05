//heap sort
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ELEMENTS 1000000
typedef struct{
	int key;
}element;
element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];
int max_n=0;
int min_n=0;
void insert_max_heap(element item, int *max_n);
void insert_min_heap(element item, int *min_n);
void print_ascend(int *min_n);
void print_descend(int *max_n);

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("usage: ./mp2 input_filename\n");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("The input file does not exist.\n");
		exit(1);
	}

	clock_t start = clock();
	
	FILE *ofp = fopen("mp2_result.txt", "w");
	char command[10]={0};
	int num=0;
	while(1){
		fscanf(fp, "%s", command);
		if(feof(fp)) break;
		if(strcmp(command, "INSERT")==0){
			fscanf(fp, "%d", &num);
			element item;
			item.key=num;
			insert_max_heap(item, &max_n);
			insert_min_heap(item, &min_n);
		}

		else if(strcmp(command, "ASCEND")==0){
			print_ascend(&min_n);
		}

		else if(strcmp(command, "DESCEND")==0){
			print_descend(&max_n);
		}
	}

	clock_t end = clock();
	printf("output written to mp2_result.txt.\n");
	printf("running time: %lf seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
	fclose(ofp);
	fclose(fp);
	return 0;
}


void insert_max_heap(element item, int *max_n){
	int i;
	i = ++(*max_n);
	if(i>1){
		while(1){
			if(item.key > max_heap[i/2].key){
				max_heap[i] = max_heap[i/2];
				i/=2;
			}
			if((item.key <= max_heap[i/2].key)||(i==1)) break;
		}
	}
	max_heap[i]=item;
}


void insert_min_heap(element item, int *min_n){
	int i;
	i = ++(*min_n);
	if(i>1){
		while(1){
			if(item.key < min_heap[i/2].key){
				min_heap[i] = min_heap[i/2];
				i/=2;
			}
			if((item.key >= min_heap[i/2].key)||(i==1)) break;
		}
	}
	min_heap[i]=item;
}


void print_ascend(int *min_n){
	FILE *ofp = fopen("mp2_result.txt", "a");
	element temp_min_heap[MAX_ELEMENTS];
	for(int i=0;i<=*min_n;i++){
		temp_min_heap[i].key=min_heap[i].key;
	}
	int i, child;
	int temp_n=*min_n;
	while(1){
		if(temp_n==0) break;
		element item, temp;
		item = temp_min_heap[1];
		temp = temp_min_heap[temp_n--];
		
		i=1;
		child=2;
		while(1){
			if(child+1<=temp_n){
				if(temp_min_heap[child].key > temp_min_heap[child+1].key){
					child++;
				}
			}
			if((temp.key <= temp_min_heap[child].key)||(child>temp_n)) break;
			if(temp.key > temp_min_heap[child].key){
				temp_min_heap[i]=temp_min_heap[child];
				i=child;
				child*=2;
			}
		}
		temp_min_heap[i]=temp;
		fprintf(ofp, "%d ", item.key);
	}
	fprintf(ofp, "\n");
	fclose(ofp);
}


void print_descend(int *max_n){
	FILE *ofp = fopen("mp2_result.txt", "a");
	element temp_max_heap[MAX_ELEMENTS];
	for(int i=0;i<=*max_n;i++){
		temp_max_heap[i].key=max_heap[i].key;
	}
	int i, child;
	int temp_n=*max_n;
	while(1){
		if(temp_n==0) break;
		element item, temp;
		item = temp_max_heap[1];
		temp = temp_max_heap[temp_n--];

		i=1;
		child=2;
		while(1){
			if(child+1<=temp_n){
				if(temp_max_heap[child].key < temp_max_heap[child+1].key){
					child++;
				}
			}
			if((temp.key >= temp_max_heap[child].key)||(child>temp_n)) break;
			if(temp.key < temp_max_heap[child].key){
				temp_max_heap[i]=temp_max_heap[child];
				i=child;
				child*=2;
			}
		}
		temp_max_heap[i]=temp;
		fprintf(ofp, "%d ", item.key);
	}
	fprintf(ofp, "\n");
	fclose(ofp);
}
