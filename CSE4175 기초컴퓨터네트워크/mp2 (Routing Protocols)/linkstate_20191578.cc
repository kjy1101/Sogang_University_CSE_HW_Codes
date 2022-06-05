#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100

int vertex_n, edge_n;
int cost[MAX][MAX];
int distance[MAX];
int visited[MAX];
int path[MAX][MAX]; //[destination][index]
int pdx[MAX];

void shortest_path(int src);
int choose_next(void);

int main(int argc, char *argv[]){

	if(argc != 4){
		fprintf(stderr, "usage: linkstate topologyfile messagesfile changesfile\n");
		exit(1);
	}

	/*
	 argv[1] : topologyfile
	 argv[2] : messagesfile
	 argv[3] : changesfile
	 */

	FILE *fp1, *fp2, *fp3, *ofp;
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	fp3 = fopen(argv[3], "r");
	ofp = fopen("output_ls.txt", "w");
	if((fp1 == NULL) || (fp2 == NULL) || (fp3 == NULL)){
		fprintf(stderr, "Error: open input file.\n");
		exit(1);
	}

	int src, det, weight;
	fscanf(fp1, "%d", &vertex_n);
	for(int i=0;i<vertex_n;i++){
		distance[i]=INT_MAX;
		visited[i]=0;
		pdx[i]=1;
		for(int j=0;j<vertex_n;j++){
			cost[i][j]=-999;
			path[i][j]=-1;																		
		}
	}
	while(1){
		fscanf(fp1, "%d %d %d", &src, &det, &weight);
		if(feof(fp1)) break;
		cost[src][det]=weight;
		cost[det][src]=weight;
	}
	fclose(fp1);

	for(int i=0;i<vertex_n;i++){
		shortest_path(i);
		for(int j=0;j<vertex_n;j++){
			if(distance[j]<INT_MAX){
				if(path[j][1] != -1){
					fprintf(ofp, "%d %d %d\n", j, path[j][1], distance[j]);
				}
				else{
					fprintf(ofp, "%d %d %d\n", j, path[j][0], distance[j]);
				}
			}
		}
		fprintf(ofp, "\n");

		/* Initialize */
		for(int j=0;j<vertex_n;j++){
			distance[j] = INT_MAX;
			visited[j] = 0;
			pdx[j] = 1;
			for(int k=0;k<vertex_n;k++){
				path[j][k] = -1;
			}
		}
	}


	char message[MAX][MAX];
	int source[MAX];
	int destination[MAX];
	int m_idx = 0;
	while(1){
		/* read messagefile */
		fscanf(fp2, "%d %d", &source[m_idx], &destination[m_idx]);
		if(feof(fp2)) break;
		if(fgets(message[m_idx++], 1000, fp2) == NULL) break;
	}
	fclose(fp2);

	
	for(int i=0;i<m_idx;i++){
		shortest_path(source[i]);
		if(distance[destination[i]]<INT_MAX){
			fprintf(ofp, "from %d to %d cost %d hops ", source[i], destination[i], distance[destination[i]]);
			for(int j=0;j<vertex_n;j++){
				if((path[destination[i]][j]!=-1)&&(path[destination[i]][j]!=destination[i])) fprintf(ofp, "%d ", path[destination[i]][j]);
			}
			fprintf(ofp, "message%s", message[i]);
		}
		else{
			fprintf(ofp, "from %d to %d cost infinite hops unreachable message%s", source[i], destination[i], message[i]);
		}
		/* Initialize */
		for(int j=0;j<vertex_n;j++){
			distance[j] = INT_MAX;
			visited[j] = 0;
			pdx[j] = 1;
			for(int k=0;k<vertex_n;k++){
				path[j][k] = -1;
			}
		}
	}
	fprintf(ofp, "\n");


	int router1=0, router2=0, newcost=0;
	while(1){
		/* read changefile */
		fscanf(fp3, "%d %d %d", &router1, &router2, &newcost);
		if(feof(fp3)) break;
		cost[router1][router2] = newcost;
		cost[router2][router1] = newcost;
		
		for(int i=0;i<vertex_n;i++){
			shortest_path(i);
			for(int j=0;j<vertex_n;j++){
				if(distance[j]<INT_MAX){
					if(path[j][1] != -1){
						fprintf(ofp, "%d %d %d\n", j, path[j][1], distance[j]);
					}
					else{
						if(path[j][0] != i) continue;
						//for(int k=0;k<vertex_n;k++) printf("%d ", path[j][k]);
						//printf("\n%d->%d를 위해 다음은 %d, 거리는 %d\n", i,j, path[j][0], distance[j]);
						fprintf(ofp, "%d %d %d\n", j, path[j][0], distance[j]);
					}
				}
			}
			fprintf(ofp, "\n");
	
			/* Initialize */
			for(int j=0;j<vertex_n;j++){
				distance[j] = INT_MAX;
				visited[j] = 0;
				pdx[j] = 1;
				for(int k=0;k<vertex_n;k++){
					path[j][k] = -1;
				}
			}
		}

		for(int i=0;i<m_idx;i++){
			shortest_path(source[i]);
			if(distance[destination[i]]<INT_MAX){
				fprintf(ofp, "from %d to %d cost %d hops ", source[i], destination[i], distance[destination[i]]);
				for(int j=0;j<vertex_n;j++){
					if((path[destination[i]][j]!=-1)&&(path[destination[i]][j]!=destination[i])) fprintf(ofp, "%d ", path[destination[i]][j]);
				}
				fprintf(ofp, "message%s", message[i]);
			}
			else{
				fprintf(ofp, "from %d to %d cost infinite hops unreachable message%s", source[i], destination[i], message[i]);
			}
			/* Initialize */
			for(int j=0;j<vertex_n;j++){
				distance[j] = INT_MAX;
				visited[j] = 0;
				pdx[j] = 1;
				for(int k=0;k<vertex_n;k++){
					path[j][k] = -1;
				}
			}
		}
		fprintf(ofp, "\n");
	}
	fclose(fp3);
	fclose(ofp);

	printf("Complete. Output file written to output_ls.txt.\n");
	return 0;
}

void shortest_path(int src){
	for(int i=0;i<vertex_n;i++){
		if(cost[src][i]>0){
			distance[i]=cost[src][i];
			path[i][1]=i;
			pdx[i]++;
		}
		else{
			distance[i] = INT_MAX;
		}
	}

	distance[src]=0;
	visited[src]=1;
	/*printf("알고리즘 타기전 distance\n");
	for(int i=0;i<vertex_n;i++){
		printf("%d ", distance[i]);
	}printf("\n");*/

	for(int i=0;i<vertex_n;i++){
		path[i][0]=src;
	}

	int node;
	for(int i=0;i<vertex_n-2;i++){
		node = choose_next();
		for(int j=0;j<vertex_n;j++){
			if((cost[node][j]>0)&&(visited[j]==0)){
				if(distance[node]+cost[node][j] < distance[j]){
					if(node == -1) continue;
					//printf("distance[%d]: %d\n", node, distance[node]);
					//printf("cost[%d][%d]: %d\n", node, j, cost[node][j]);
					//printf("sum: %d\n", distance[node]+cost[node][j]);
					//printf("distance[%d]: %d\n", j, distance[j]);
					distance[j]=distance[node]+cost[node][j];
					//경로갱신 path[j][]에 path[node][]를 복사한다.
					for(int k=0;k<MAX;k++){
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

	/*printf("시작점: %d\n", src);
	for(int i=0;i<vertex_n;i++){
		printf("%d ", distance[i]);
	}printf("\n");
	printf("현재 cost 상황\n");
	for(int i=0;i<vertex_n;i++){
		for(int j=0;j<vertex_n;j++){
			printf("%4d ", cost[i][j]);
		}printf("\n");
	}printf("\n");*/

	/*for(int i=0;i<vertex_n;i++){
		if(distance[i]<INT_MAX){
			printf("SRC: %d, DST: %d, LENGTH: %d, PATH:", src, i, distance[i]);
			for(int j=0;j<vertex_n;j++){
				if((path[i][j]!=-1)&&(path[i][j]!=i)) printf(" %d", path[i][j]);
			}
			printf(" %d\n", i);
		}
		else
			printf("SRC: %d, DST: %d, LENGTH: -, PATH: -\n", src, i);
	}*/
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
