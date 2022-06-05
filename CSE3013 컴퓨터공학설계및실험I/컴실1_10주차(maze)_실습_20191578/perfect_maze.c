//perfect_maze
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_HEIGHT 100
#define MAX_WIDTH 100
#define WALL 4

int maze[MAX_HEIGHT][MAX_WIDTH][WALL+1];
void change_all_numbers(int a, int b);
void print_maze(int h, int w);
int n, m;

int main(void){
	srand(time(NULL));
	int count=1;
	scanf("%d %d", &n, &m);
	//maze 초기화
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			maze[i][j][0]=count++;
			for(int k=1;k<=WALL;k++){
				maze[i][j][k]=1;
			}
		}
	}
	for(int k=0;k<m;k++){
		maze[k][n][0]=0;
	}
	
	int i;
	for(i=0;i<m-1;i++){
		int random=0;
		//vertical wall delete(left[3], right[4])
		for(int j=0;j<n-1;j++){
			if(maze[i][j][0] != maze[i][j+1][0]){
				//오른쪽 칸과 속해있는 집합이 다르다
				//현재칸의 오른쪽벽과 오른쪽칸의 왼쪽벽을 제거 or 유지?
				random = rand()%4;
				if(random>1){
					//random값이 1보다 크면 제거한다.
					maze[i][j][4]=0;
					maze[i][j+1][3]=0;
					if(maze[i][j][0] <= maze[i][j+1][0])
						change_all_numbers(maze[i][j][0], maze[i][j+1][0]);
					
					else
						change_all_numbers(maze[i][j+1][0], maze[i][j][0]);
				}
			}
		}
	
		//horizontal wall delete(up[1], down[2])
		int extension_flag=0;
		for(int j=0;j<n;j++){
			//현재칸의 아래쪽벽과 아래칸의 위쪽벽을 제거한다.
			if((maze[i][j][1]==1)&&(maze[i][j][3]==1)&&(maze[i][j][4]==1)){
				//현재칸의 위, 왼쪽, 오른쪽 벽이 세워져있으면 무조건 아래칸을 뚫는다.
				maze[i][j][2]=0;
				maze[i+1][j][1]=0;
				maze[i+1][j][0]=maze[i][j][0];
				extension_flag=1;
			}
			else{
				//다른 벽이 뭐 하나라도 뚫려있으면 랜덤으로 제거 or 유지 선택
				random = rand()%4;
				if(random>1){
					//random값이 1보다 크면 제거한다.
					maze[i][j][2]=0;
					maze[i+1][j][1]=0;
					maze[i+1][j][0]=maze[i][j][0];
					extension_flag=1;
				}
				else{
					//random값이 1보다 작거나 같으면 유지한다.
				}
			}
			if(maze[i][j][0]!=maze[i][j+1][0]){
				if(extension_flag==0){
					//[0]집합에 속한 마지막 칸인데 이전까지 하나도 확장을 안했다면 확장
					maze[i][j][2]=0;
					maze[i+1][j][1]=0;
					maze[i+1][j][0]=maze[i][j][0];
				}
				extension_flag=0;
			}
		}
	}
	//마지막 줄
	i=m-1;
	for(int j=0;j<n-1;j++){
		if(maze[i][j][0]!=maze[i][j+1][0]){
			//인접한 칸이 서로 다른 집합에 속해있음
			maze[i][j][4]=0;
			maze[i][j+1][3]=0;
			if(maze[i][j][0] <= maze[i][j+1][0])
				change_all_numbers(maze[i][j][0], maze[i][j+1][0]);
			else
				change_all_numbers(maze[i][j+1][0], maze[i][j][0]);

		}
	}

/*	for(int i=0;i<m;i++){
		for(int j=0;j<=n;j++){
			printf("maze[%d][%d] ID: %d, up: %d, down: %d, left: %d, right: %d\n", i, j, maze[i][j][0], maze[i][j][1], maze[i][j][2], maze[i][j][3], maze[i][j][4]);
		}
	}*/

	print_maze(m, n);
	return 0;
}

void change_all_numbers(int a, int b){
	//b를 모두 a로
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(maze[i][j][0]==b)
				maze[i][j][0]=a;
		}
	}
}

void print_maze(int h, int w){
	FILE *fp = fopen("maze.maz", "w");
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			fprintf(fp, "+");
			if(maze[i][j][1]==1){
				fprintf(fp, "-");
			}
			else{
				fprintf(fp, " ");
			}
		}
		fprintf(fp, "+\n");
		for(int j=0;j<w;j++){
			if(maze[i][j][3]==1){
				fprintf(fp, "| ");
			}
			else{
				fprintf(fp, "  ");
			}
		}
		fprintf(fp, "|\n");
		if(i==h-1){
			for(int j=0;j<w;j++){
				fprintf(fp, "+");
				if(maze[i][j][2]==1){
					fprintf(fp, "-");
				}
			}
			fprintf(fp, "+\n");
		}
	}
	fclose(fp);
}
