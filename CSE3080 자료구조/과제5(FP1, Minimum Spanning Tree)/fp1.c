#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VER 10000
#define MAX_EDGE 50000000

int vertex_n=0;
int edge_n=0;

//min heap
typedef struct{
	int v1, v2, key;
}element;
int min_n=0;
element min_heap[MAX_EDGE];
void insert_min_heap(element item, int *min_n);
element choose_min_cost(int *min_n);

//disjoint set
int Disjoint_set[MAX_VER];
int rank[MAX_VER];
int find_top_parent(int x);
int merge_tree(int x, int y);

//result T
element T[MAX_EDGE];
int Tn=0;

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("usage: ./fp1 input_filename\n");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("The input file does not exist.\n");
		exit(1);
	}

	clock_t start = clock();
	FILE *ofp = fopen("fp1_result.txt", "w");

	int vertex1, vertex2, weight;
	fscanf(fp, "%d %d", &vertex_n, &edge_n);
	while(1){
		fscanf(fp, "%d", &vertex1);
		if(feof(fp)) break;
		fscanf(fp, "%d %d", &vertex2, &weight);
		element item;
		item.v1=vertex1;
		item.v2=vertex2;
		item.key=weight;
		insert_min_heap(item, &min_n);
	}

	for(int i=0;i<vertex_n;i++){
		Disjoint_set[i]=i;
		rank[i]=0;
	}

	int sum=0;
	while((Tn < vertex_n-1)&&(min_n!=0)){
		element min_cost = choose_min_cost(&min_n);
		int flag = merge_tree(min_cost.v1, min_cost.v2);
		if(flag!=0){
			T[Tn++]=min_cost;
			sum += min_cost.key;
		}
	}

	for(int i=0;i<Tn;i++){
		fprintf(ofp, "%d %d %d\n", T[i].v1, T[i].v2, T[i].key);
	}
	
	fprintf(ofp, "%d\n", sum);

	if(Tn < vertex_n-1){
		fprintf(ofp, "DISCONNECTED");
	}
	else{
		fprintf(ofp, "CONNECTED\n");
	}

	clock_t end = clock();
	printf("output written to fp1_result.txt.\n");
	printf("running time: %lf seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
	fclose(ofp);
	fclose(fp);
	return 0;
}



void insert_min_heap(element item, int *min_n){
	int i;
	i = ++(*min_n);
	if(i>1){
		while(1){
			if(item.key < min_heap[i/2].key){
				min_heap[i]=min_heap[i/2];
				i/=2;
			}
			if((item.key >= min_heap[i/2].key)||(i==1)) break;
		}
	}
	min_heap[i]=item;
}



element choose_min_cost(int *min_n){
	element item, temp;
	item = min_heap[1];
	temp = min_heap[(*min_n)--];
	int i=1;
	int child=2;
	while(1){
		if(child+1 <= *min_n){
			if(min_heap[child].key > min_heap[child+1].key) child++;
		}
		if (child > *min_n) break;
		if(temp.key <= min_heap[child].key) break;
		if(temp.key > min_heap[child].key){
			min_heap[i]=min_heap[child];
			i=child;
			child*=2;
		}
	}
	min_heap[i]=temp;
	return item;
}


int find_top_parent(int x){
	if(Disjoint_set[x]==x) return x;
	Disjoint_set[x] = find_top_parent(Disjoint_set[x]);
	return Disjoint_set[x];
}


int merge_tree(int x, int y){
	int Px = find_top_parent(x);
	int Py = find_top_parent(y);
	if(Px==Py) return 0;
	else{
		if(rank[Px] > rank[Py]) Disjoint_set[Py] = Px;
		else if(rank[Px] < rank[Py]) Disjoint_set[Px] = Py;
		else if(rank[Px] == rank[Py]){
			Disjoint_set[Py] = Px;
			rank[Px]++;
		}
		return 1;
	}
}
