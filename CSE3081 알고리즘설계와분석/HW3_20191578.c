#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
	long int v1, v2;
	long long int weight;
}element;
element *min_heap;
void insert_min_heap(element item, long long int *min_n);
element choose_min_cost(long long int *min_n);

typedef struct {
	long int parent;
	long int v;
	int rank;
}node;
node *Disjoint_set;
long int find_top_parent(long int x);
int merge_tree(long int x, long int y, long long int w);

typedef struct {
	long int vertex;
	long long int weight;
	struct MST_node *next;
}MST_node;

typedef struct {
	long int vertex;
	long long int weight;
}stack_node;

MST_node** MST;
long long int dfs(MST_node **mst, long int v, long int n_vertex, long int *num);
long int *visited;

//long long int kscanned=0;

int main(void) {
	FILE *cfp = fopen("commands.txt", "r");
	if (cfp == NULL) {
		printf("No input file.\n");
		exit(0);
	}
	char inName[100]; char outName[100];
	fscanf(cfp, "%s %s", inName, outName);
	fclose(cfp);

	FILE *infp = fopen(inName, "r");
	if (infp == NULL) {
		printf("No input file.\n");
		exit(0);
	}
	long int n_vertex;
	long long int n_edge, max_weight;
	fscanf(infp, "%ld %lld %lld", &n_vertex, &n_edge, &max_weight);

	min_heap = (element*)malloc(sizeof(element)*(n_edge + 1));
	Disjoint_set = (node*)malloc(sizeof(node)*(n_vertex + 1));
	visited = (long int*)malloc(sizeof(long int)*n_vertex);
	

	MST_node** MST = (MST_node**)malloc(sizeof(MST_node)*n_vertex);
	for (long int i = 0; i < n_vertex; i++) {
		MST[i] = (MST_node*)malloc(sizeof(MST_node));
		MST[i]->next = NULL;
		MST[i]->vertex = i;
		MST[i]->weight = 0;
	}

	long int v1, v2;
	long long int w;
	long long int min_n = 0;

//	clock_t start1, start2, end1, end2;
//	float res1, res2;
//	start1 = clock();
//	start2 = clock();
	while (1) {
		fscanf(infp, "%ld", &v1);
		if (feof(infp)) break;
		fscanf(infp, "%ld %lld", &v2, &w);
		element item;
		item.v1 = v1;
		item.v2 = v2;
		item.weight = w;
		insert_min_heap(item, &min_n);
	}
//	end2 = clock();
	fclose(infp);

	for (long int i = 0; i < n_vertex; i++) {
		Disjoint_set[i].parent = i;
		Disjoint_set[i].v = i;
		Disjoint_set[i].rank = 0;
	}
//	long long int k = 0;
	while (min_n > 0) {
		element next_edge = choose_min_cost(&min_n);
	
		int flag = 0;
		flag = merge_tree(next_edge.v1, next_edge.v2, next_edge.weight);
//		if (kscanned >= n_vertex-1) k++;
		if (flag == 1) {
			//병합
			MST_node *newnode1 = (MST_node*)malloc(sizeof(MST_node));
			MST_node *newnode2 = (MST_node*)malloc(sizeof(MST_node));
			newnode1->vertex = next_edge.v1;
			newnode2->vertex = next_edge.v2;
			newnode1->weight = next_edge.weight;
			newnode2->weight = next_edge.weight;
			newnode1->next = MST[next_edge.v2]->next;
			newnode2->next = MST[next_edge.v1]->next;
			MST[next_edge.v1]->next = newnode2;
			MST[next_edge.v2]->next = newnode1;
		}
	}
	
/*	for (int i = 0; i < n_vertex; i++) {
		MST_node *cur = MST[i];
		//	printf("total weight: %d\n", cur->weight);
		while (cur != NULL) {
			printf("%d[%d] ", cur->vertex, cur->weight);
			cur = cur->next;
		}
		printf("\n");
	}
	*/
	int count = 0;
	for (long int i = 0; i < n_vertex; i++) {
		if (Disjoint_set[i].parent == i) count++;
	}


	FILE *ofp = fopen(outName, "w");
	fprintf(ofp, "%d\n", count);
	for (long int i = 0; i < n_vertex; i++) {
		long int num = 0;
		if (Disjoint_set[i].parent == i) {
			long long int result = dfs(MST, i, n_vertex, &num);
			fprintf(ofp, "%ld %lld\n", num, result);
		}
	}
	fclose(ofp);

//	end1 = clock();

//	res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
//	res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
//	printf("전체 수행 시간: %.3f\n", res1);
//	printf("민힙 구축 시간: %.3f\n", res2);
//	printf("kscanned: %lld\n", n_edge-k+1);

	return 0;
}

void insert_min_heap(element item, long long int *min_n) {
	long long int i;
	i = ++(*min_n);
	if (i > 1) {
		while (1) {
			if (item.weight < min_heap[i / 2].weight) {
				min_heap[i] = min_heap[i / 2];
				i /= 2;
			}
			if ((item.weight >= min_heap[i / 2].weight) || (i == 1)) break;
		}
	}
	min_heap[i] = item;
}

element choose_min_cost(long long int *min_n) {
	element item, temp;
	item = min_heap[1];
	temp = min_heap[(*min_n)--];
	long int parent = 1;
	long int child = 2;

	while (child <= *min_n) {
		if ((child < *min_n) && (min_heap[child].weight > min_heap[child + 1].weight)) child++;
		if (temp.weight <= min_heap[child].weight) break;
		min_heap[parent] = min_heap[child];
		parent = child;
		child *= 2;
	}

	min_heap[parent] = temp;
	return item;
}

long int find_top_parent(long int x) {
	if (Disjoint_set[x].parent == x) return x;
	Disjoint_set[x].parent = find_top_parent(Disjoint_set[x].parent);
	return Disjoint_set[x].parent;
}


int merge_tree(long int x, long int y, long long int w) {
	long int Px = find_top_parent(x);
	long int Py = find_top_parent(y);
	if (Px == Py) return 0;
	else {
		if (Disjoint_set[Px].rank > Disjoint_set[Py].rank) {
			Disjoint_set[Py].parent = Px; //Px가 부모로
		}
		else if (Disjoint_set[Px].rank < Disjoint_set[Py].rank) {
			Disjoint_set[Px].parent = Py; //Py가 부모로
		}
		else if (Disjoint_set[Px].rank == Disjoint_set[Py].rank) {
			Disjoint_set[Py].parent = Px; //Px가 부모로
			Disjoint_set[Px].rank++;
		}
	//	kscanned++;
		return 1;
	}
}

long long int dfs(MST_node **mst, long int s, long int n_vertex, long int *num) {
	long long int total_weight = 0;
	stack_node* stack;
	stack = (stack_node*)malloc(sizeof(stack_node)*n_vertex);
	for (long int i = 0; i < n_vertex; i++) {
		stack[i].vertex = 0;
		stack[i].weight = 0;
		visited[i] = 0;
	}
	long int idx = 0;
	stack[idx++].vertex = s;
	while (idx != 0) {
		long int v = stack[--idx].vertex;
//		printf("selected vertex: %d\n", v);
		long long int w = stack[idx].weight;
//		printf("selected weight: %d\n", w);
		if (visited[v] == 0) {
			visited[v] = 1; (*num)++;
			total_weight += w;
			MST_node *cur = mst[v]->next;
			while (cur != NULL) {
			//	printf("cur->vertex: %d\n", cur->vertex);
				if (visited[cur->vertex] == 0) {
					stack[idx].vertex = cur->vertex;
					stack[idx++].weight = cur->weight;
				}
				cur = cur->next;
			}
		}
	}
	return total_weight;
}