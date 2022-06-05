#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100
/* routing table element */
struct node{
	int dest; //목적지
	int next; //다음
	int cost; //거리
};

struct table{
	struct node *d;
};

/* network router element */
struct router_node{
	int ID; //my router number
	int cost[MAX]; //connect:cost, disconnect:-999
};

struct table *table;
struct router_node *network;

void exchange(int router_num);
int find_path(int source, int dest, int router_num, int path[]); //success:0, fail:1

int main(int argc, char *argv[]){

	if(argc != 4){
		fprintf(stderr, "usage: distvec topologyfile messagesfile changesfile\n");
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
	ofp = fopen("output_dv.txt", "w");
	if((fp1 == NULL) || (fp2 == NULL) || (fp3 == NULL)){
		fprintf(stderr, "Error: open input file.\n");
		exit(1);
	}

	/* Initialize network */
	int router_num = 0;
	int router1=0, router2=0, cost=0;
	fscanf(fp1, "%d", &router_num);

	network = (struct router_node*)malloc(sizeof(struct router_node)*router_num);
	for(int i=0;i<router_num;i++){
		network[i].ID = i;
		for(int j=0;j<router_num;j++){
			network[i].cost[j] = -999; //disconnect(initial)
		}
		network[i].cost[i] = 0; //self
	}
	
	while(1){
		/* read topologyfile */
		fscanf(fp1, "%d %d %d", &router1, &router2, &cost);
		if(feof(fp1)) break;
		network[router1].cost[router2] = cost;
		network[router2].cost[router1] = cost;
	}
	fclose(fp1);

	/* Initialize routing table */
	table = (struct table*)malloc(sizeof(struct table)*router_num);
	for(int i=0;i<router_num;i++){ //i의 table
		table[i].d = (struct node*)malloc(sizeof(struct node)*router_num);
		for(int j=0;j<router_num;j++){ //목적지 j로 가는
			table[i].d[j].dest = j;
			if(network[i].cost[j] != -999){ //connected directly
				table[i].d[j].next = j;
				table[i].d[j].cost = network[i].cost[j];
			}else{ //disconnected directly
				table[i].d[j].next = INT_MAX;
				table[i].d[j].cost = INT_MAX;
			}
		}
	}

	/* First routing table */
	exchange(router_num);
	for(int i=0;i<router_num;i++){
		for(int j=0;j<router_num;j++){
			if(table[i].d[j].cost != INT_MAX){
				fprintf(ofp, "%d %d %d\n", table[i].d[j].dest, table[i].d[j].next, table[i].d[j].cost);
			}
		}
		fprintf(ofp, "\n");
	}
	
	char message[MAX][MAX];
	int source[MAX];
	int destination[MAX];
	int m_idx = 0;
	int path[MAX];
	while(1){
		/* read messagefile */
		fscanf(fp2, "%d %d", &source[m_idx], &destination[m_idx]);
		if(feof(fp2)) break;
		if(fgets(message[m_idx++], 1000, fp2) == NULL) break;
	}
	fclose(fp2);

	
	for(int i=0;i<m_idx;i++){
		if(find_path(source[i], destination[i], router_num, path)==0){
			int idx=0;
			fprintf(ofp, "from %d to %d cost %d hops ", source[i], destination[i], table[source[i]].d[destination[i]].cost);
			while(1){
				fprintf(ofp, "%d ", path[idx++]);
				if(path[idx] == destination[i]) break;
			}
			fprintf(ofp, "message%s", message[i]);
		}
		else{
			fprintf(ofp, "from %d to %d cost infinite hops unreachable message%s", source[i], destination[i], message[i]);
		}
	}
	fprintf(ofp, "\n");




	while(1){
		/* read changefile */
		fscanf(fp3, "%d %d %d", &router1, &router2, &cost);
		if(feof(fp3)) break;
		network[router1].cost[router2] = cost;
		network[router2].cost[router1] = cost;
		for(int i=0;i<router_num;i++){
			if(table[router1].d[i].next == router2){
				table[router1].d[i].next = INT_MAX;
				table[router1].d[i].cost = INT_MAX;
			}
			if(table[router2].d[i].next == router1){
				table[router2].d[i].next = INT_MAX;
				table[router2].d[i].cost = INT_MAX;
			}
		}


		for(int i=0;i<router_num;i++){ //i의 table
			for(int j=0;j<router_num;j++){ //목적지 j로 가는
				if(network[i].cost[j] != -999){ //connected directly
					table[i].d[j].next = j;
					table[i].d[j].cost = network[i].cost[j];
				}else{ //disconnected directly
					table[i].d[j].next = INT_MAX;
					table[i].d[j].cost = INT_MAX;
				}
			}
		}


		exchange(router_num);
		for(int i=0;i<router_num;i++){
			for(int j=0;j<router_num;j++){
				if(table[i].d[j].cost != INT_MAX){
					fprintf(ofp, "%d %d %d\n", table[i].d[j].dest, table[i].d[j].next, table[i].d[j].cost);
				}
			}
			fprintf(ofp, "\n");
		}



		for(int i=0;i<m_idx;i++){
			if(find_path(source[i], destination[i], router_num, path)==0){
				int idx=0;
				fprintf(ofp, "from %d to %d cost %d hops ", source[i], destination[i], table[source[i]].d[destination[i]].cost);
				while(1){
					fprintf(ofp, "%d ", path[idx++]);
					if(path[idx] == destination[i]) break;
				}
				fprintf(ofp, "message%s", message[i]);
			}
			else{
				fprintf(ofp, "from %d to %d cost infinite hops unreachable message%s", source[i], destination[i], message[i]);
			}
		}
		fprintf(ofp, "\n");
	}

	fclose(fp3);
	fclose(ofp);
	
	printf("Complete. Output file written to output_dv.txt.\n");
	return 0;
}



void exchange(int router_num){
	/* exchange routing table */
	int temp = 0;
	while(1){
		for(int i=0;i<router_num;i++){
			/* update i's table - table[i]*/
			for(int j=0;j<router_num;j++){ //compare with table[j]
				if(i==j) continue; //compare i with i's table
				if(network[i].cost[j] == -999) continue; //disconnected node's table
				for(int k=0;k<router_num;k++){ //table[j].d[k] - i/j's table, dest k
					if((i==k) || (j==k)) continue; //node itself
					int distance = network[i].cost[j];
					if(table[j].d[k].cost == INT_MAX) continue;
					if(table[i].d[k].cost > table[j].d[k].cost + distance){
						//printf("바꿀 테이블: %d\n", i);
						//printf("%d로부터 받음\n", j);
						//printf("%d부터 %d로 가는 경로\n",i,k);
						//printf("%d에서 %d로 바꾼다.\n", table[i].d[k].cost, table[j].d[k].cost+distance);
						table[i].d[k].cost = table[j].d[k].cost + distance;
						table[i].d[k].next = j;
						temp = 1;
					}
				}
			}
		}
		if(temp == 0) break;
		temp = 0;
	}
}



int find_path(int source, int dest, int router_num, int path[]){
	int path_idx = 0;
	int hop = source;
	path[path_idx++] = hop;
	while(1){
		hop = table[hop].d[dest].next;
		path[path_idx++] = hop;
		if(hop == dest) break;
		if(hop == INT_MAX) return 1;
	}
	return 0;
}
