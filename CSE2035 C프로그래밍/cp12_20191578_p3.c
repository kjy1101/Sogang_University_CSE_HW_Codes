#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n; //지뢰판 크기
	int** ground; //지뢰판
	int m; //지뢰의 개수
	int** bomb_loc; //지뢰의 위치
	int choice; //선택할 칸의 개수
	int* mychoice; //선택한 칸의 위치

	scanf("%d", &n); //지뢰판 크기 입력받기
	ground = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		*(ground + i) = (int*)calloc(n, sizeof(int));
	} //지뢰판 크기 동적할당


	scanf("%d", &m); //지뢰의 개수 입력받기
	bomb_loc = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		*(bomb_loc+i) = (int*)malloc(2 * sizeof(int));
	} //지뢰의 위치를 받을 2차원배열 bomb_loc 크기 동적할당하기

	for (int i = 0; i < m; i++) {
		scanf("%d %d", *(bomb_loc + i), *(bomb_loc + i) + 1);
	} //지뢰 좌표 입력받기

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 2; j++)
			*(*(bomb_loc + i) + j) -= 1;
	} //입력받을 때 (1,1)이 2차원배열에서 (0,0)이므로 모든 요소에서 1씩 뺀다.

	int col, row;
	for (int i = 0; i < m; i++) {
		col = *(*(bomb_loc + i));
		row = *(*(bomb_loc+i)+1);
		*(*(ground+col)+row) = 1;
	}
	//지뢰는 1로 표시


	scanf("%d", &choice); //칸을 몇번 선택할지 입력받기
	mychoice = (int*)malloc(2 * sizeof(int)); //선택한 칸의 좌표, 그때그때 초기화
	int count = 0; //주변에 있는 지뢰 개수

	for (int i = 0; i < choice; i++) {
		scanf("%d %d", mychoice, mychoice + 1);
		*mychoice -= 1; *(mychoice + 1) -= 1; //입력받을 때 (1,1)이 2차원배열에서 (0,0)이므로 모든 요소에서 1씩 뺀다.

		for (int k = *mychoice - 1; k <= (*mychoice) + 1; k++) {
			for (int l = *(mychoice + 1) - 1; l <= *(mychoice + 1) + 1; l++) {
				if (k >= 0 && l >= 0 && k < n && l < n) {
					if (*(*(ground + k) + l) == 1) count++;
				}
			}
		}

		if (*(*(ground + *mychoice) + *(mychoice + 1)) != 1) {
			printf("Number of mine = %d\n", count);
			count = 0;
		}
		
		else {
			printf("BOMB\n");
			break;
		}
	}

	return 0;
}