//shortest path
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define MAX_VER 10000
#define MAX_EDGE 100000000

int vertex_n, edge_n;
int cost[MAX_VER][MAX_VER];
int distance[MAX_VER];
int visited[MAX_VER];
int path[MAX_VER][MAX_VER]; //[destination][index]
int pdx[MAX_VER];

int shortest_path(int src);
int choose_next(void);

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("usage: ./fp2 input_filename\n");
		exit(1);
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("The input file does not exist.\n");
		exit(1);
	}

	clock_t start = clock();
	FILE *ofp = fopen("fp2_result.txt", "w");

	int src, det, weight;
	fscanf(fp, "%d %d", &vertex_n, &edge_n);
	for(int i=0;i<vertex_n;i++){
		distance[i]=INT_MAX;
		visited[i]=0;
		pdx[i]=1;
		for(int j=0;j<vertex_n;j++){
			cost[i][j]=0;
			path[i][j]=-1;
		}
	}

	while(1){
		fscanf(fp, "%d", &src);
		if(feof(fp)) break;
		fscanf(fp, "%d", &det);
		if(feof(fp)) break;
		fscanf(fp, "%d", &weight);
		cost[src][det]=weight;
	}

	shortest_path(src);

	clock_t end = clock();
	printf("output written to fp2_result.txt.\n");
	printf("running time: %lf seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
	fclose(ofp);
	fclose(fp);
	return 0;

}

int shortest_path(int src){
	FILE *ofp = fopen("fp2_result.txt", "a");
	for(int i=0;i<vertex_n;i++){
		if(cost[src][i]>0){
			distance[i]=cost[src][i];
			path[i][1]=i;
			pdx[i]++;
		}
	}

	distance[src]=0;
	visited[src]=1;

	for(int i=0;i<vertex_n;i++){
		path[i][0]=src;
	}

	int node;
	for(int i=0;i<vertex_n-2;i++){
		node = choose_next();
		for(int j=0;j<vertex_n;j++){
			if((cost[node][j]>0)&&(visited[j]==0)){
				if(distance[node]+cost[node][j] < distance[j]){
					distance[j]=distance[node]+cost[node][j];
					//경로갱신 path[j][]에 path[node][]를 복사한다.
					for(int k=0;k<MAX_VER;k++){
						path[j][k]=-1;
					}
					for(int k=0;k<pdx[node];k++){
						path[j][k]=path[node][k];
					}
					pdx[j]=pdx[node];
					path[j][pdx[j]++]=j;
				}
			}
		}
	}

	for(int i=0;i<vertex_n;i++){
		if(distance[i]<INT_MAX){
			fprintf(ofp, "SRC: %d, DST: %d, LENGTH: %d, PATH:", src, i, distance[i]);
			for(int j=0;j<vertex_n;j++){
				if((path[i][j]!=-1)&&(path[i][j]!=i)) fprintf(ofp, " %d", path[i][j]);
			}
			fprintf(ofp, " %d\n", i);
		}
		else
			fprintf(ofp, "SRC: %d, DST: %d, LENGTH: -, PATH: -\n", src, i);
	}
	fclose(ofp);
}

int choose_next(void){
	int min=INT_MAX;
	int next=-1;
	for(int i=0;i<vertex_n;i++){
		if((distance[i]<min)&&(visited[i]==0)){
			min=distance[i];
			next=i;
		}
	}
	visited[next]=1;
	return next;
}
