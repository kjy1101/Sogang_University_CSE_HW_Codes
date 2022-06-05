#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n; //������ ũ��
	int** ground; //������
	int m; //������ ����
	int** bomb_loc; //������ ��ġ
	int choice; //������ ĭ�� ����
	int* mychoice; //������ ĭ�� ��ġ

	scanf("%d", &n); //������ ũ�� �Է¹ޱ�
	ground = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		*(ground + i) = (int*)calloc(n, sizeof(int));
	} //������ ũ�� �����Ҵ�


	scanf("%d", &m); //������ ���� �Է¹ޱ�
	bomb_loc = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		*(bomb_loc+i) = (int*)malloc(2 * sizeof(int));
	} //������ ��ġ�� ���� 2�����迭 bomb_loc ũ�� �����Ҵ��ϱ�

	for (int i = 0; i < m; i++) {
		scanf("%d %d", *(bomb_loc + i), *(bomb_loc + i) + 1);
	} //���� ��ǥ �Է¹ޱ�

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 2; j++)
			*(*(bomb_loc + i) + j) -= 1;
	} //�Է¹��� �� (1,1)�� 2�����迭���� (0,0)�̹Ƿ� ��� ��ҿ��� 1�� ����.

	int col, row;
	for (int i = 0; i < m; i++) {
		col = *(*(bomb_loc + i));
		row = *(*(bomb_loc+i)+1);
		*(*(ground+col)+row) = 1;
	}
	//���ڴ� 1�� ǥ��


	scanf("%d", &choice); //ĭ�� ��� �������� �Է¹ޱ�
	mychoice = (int*)malloc(2 * sizeof(int)); //������ ĭ�� ��ǥ, �׶��׶� �ʱ�ȭ
	int count = 0; //�ֺ��� �ִ� ���� ����

	for (int i = 0; i < choice; i++) {
		scanf("%d %d", mychoice, mychoice + 1);
		*mychoice -= 1; *(mychoice + 1) -= 1; //�Է¹��� �� (1,1)�� 2�����迭���� (0,0)�̹Ƿ� ��� ��ҿ��� 1�� ����.

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