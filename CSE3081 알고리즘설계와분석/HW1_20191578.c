#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
int find_max(int a, int b, int c, int *which);
int Algorithm1(int* array, int start, int end, int *s_idx, int *e_idx);
int Algorithm2(int* arr, int *start, int* finish, int n);
int Algorithm3(int** matrix, int *idx_i, int *idx_j, int *idx_k, int *idx_l, int n);
int Algorithm4(int** matrix, int *idx_i, int *idx_j, int *idx_k, int *idx_l, int n);
int Algorithm5(int** matrix, int *idx_i, int *idx_j, int *idx_k, int *idx_l, int n);

int main(void) {
	//파일 열기
	FILE *fp;
	fp = fopen("HW1_config.txt", "r");
	if (fp == NULL) {
		printf("File open error.\n");
		return 0;
	}
//	printf("File [HW1_config.txt] opened.\n");

	//config.txt 파일 읽기
	int testcase;
	int algoN;
	char inName[32], outName[32];
	fscanf(fp, "%d", &testcase);
	for (int A = 0; A < testcase; A++) {
		fscanf(fp, "%d %s %s", &algoN, inName, outName);
	//	printf("number of algorithm: %d\n", algoN);
	//	printf("input file name:     %s\n", inName);
	//	printf("output file name:    %s\n\n", outName);
		//각각의 input 파일 열고 output 파일 만들기
		FILE *infp;
		FILE *outfp;
		infp = fopen(inName, "rb");
		outfp = fopen(outName, "wb");
		if (infp == NULL) {
			printf("File open error.\n");
			return;
		}
	//	printf("File [%s] opened.\n", inName);
		int n; //n은 배열의 크기(1차원: n, 2차원: n*n)
		fread(&n, sizeof(n), 1, infp);
	//	printf("n is %d\n", n);
		//1D인지 2D인지 확인, 그에 따라 배열 할당
		int *arr; //1D일 때
		int **matrix; //2D일 때
		if ((algoN==1)||(algoN==2)) { //1D일 때
		//	printf("1D\n");
			arr = (int*)malloc(sizeof(int)*n);
			int idx = 0;
			while (1) {
				fread(&arr[idx], sizeof(int), 1, infp);
			//	if (feof(infp)==NULL) break;
				if (idx == n - 1) break;
				idx++;
			}
		//	printf("\n\n");
		/*	for (int a = 0; a < n; a++) {
				printf("%d ", arr[a]);
			}
			printf("\n");*/
			if (algoN == 1) {
				int s_idx = 0;
				int e_idx = 0;
				int result = Algorithm1(arr, 0, n-1, &s_idx, &e_idx);
				printf("Algorithm1. result is %d in line [%d, %d].\n", result, s_idx, e_idx);
				fwrite(&result, sizeof(int), 1, outfp);
				fwrite(&s_idx, sizeof(int), 1, outfp);
				fwrite(&e_idx, sizeof(int), 1, outfp);
			}
			else if (algoN == 2) {
				int start = 0, finish = 0;
				int result = Algorithm2(arr, &start, &finish, n);
				printf("Algorithm2. result is %d in line [%d, %d].\n", result, start, finish);
				fwrite(&result, sizeof(int), 1, outfp);
				fwrite(&start, sizeof(int), 1, outfp);
				fwrite(&finish, sizeof(int), 1, outfp);
			}
		}

		else { //2D일 때
			matrix = (int**)malloc(sizeof(int*)*n);
			for (int i = 0; i < n; i++) {
				matrix[i] = (int*)malloc(sizeof(int)*n);
			}
			int row = 0, col = 0;
			while (1) {
				fread(&matrix[row][col], sizeof(int), 1, infp);
			//	if (feof(infp)==NULL) break;
				if ((row == n - 1) && (col == n - 1)) break;
				col++;
				if (col >= n) {
					row++;
					col = 0;
				}
			}

		/*	for (int a = 0; a < n; a++) {
				for (int b = 0; b < n; b++) {
					printf("%d ", matrix[a][b]);
				}
				printf("\n");
			}
			printf("\n");*/
			int idx_i, idx_j, idx_k, idx_l;
			int result;
			if (algoN == 3) {
				result = Algorithm3(matrix, &idx_i, &idx_j, &idx_k, &idx_l, n);
				printf("Algorithm3. result is %d in rectangle (%d, %d, %d, %d).\n", result, idx_k, idx_i, idx_l, idx_j);
			}
			else if (algoN == 4) {
				result = Algorithm4(matrix, &idx_i, &idx_j, &idx_k, &idx_l, n);
				printf("Algorithm4. result is %d in rectangle (%d, %d, %d, %d).\n", result, idx_k, idx_i, idx_l, idx_j);
			}
			else if (algoN == 5) {
				result = Algorithm5(matrix, &idx_i, &idx_j, &idx_k, &idx_l, n);
				printf("Algorithm5. result is %d in rectangle (%d, %d, %d, %d).\n", result, idx_k, idx_i, idx_l, idx_j);
			}

			fwrite(&result, sizeof(int), 1, outfp);
			fwrite(&idx_k, sizeof(int), 1, outfp);
			fwrite(&idx_i, sizeof(int), 1, outfp);
			fwrite(&idx_l, sizeof(int), 1, outfp);
			fwrite(&idx_j, sizeof(int), 1, outfp);
		}
		fclose(infp);
		fclose(outfp);
	}
	fclose(fp);
	return 0;
}


int find_max(int a, int b, int c, int *which) {
	if (a > b) {
		if (a > c) {
			*which = 0;
			return a;
		}
		else {
			*which = 2;
			return c;
		}
	}
	else {
		if (b > c) {
			*which = 1;
			return b;
		}
		else {
			*which = 2;
			return c;
		}
	}
}

//Algorithm1: 1D, Divide and Conquer를 이용한 방법
int Algorithm1(int* array, int start, int end, int *s_idx, int *e_idx) {
	int left_s_idx = 0;
	int left_e_idx = 0;
	int right_s_idx = 0;
	int right_e_idx = 0;
	int mid_s_idx = 0;
	int mid_e_idx = 0;
	int which = 0;

	if (start == end) {
		*s_idx = start;
		*e_idx = end;
		return array[start];
	}
	int mid, leftMaxsum, rightMaxsum;
	mid = (start + end) / 2;
	leftMaxsum = Algorithm1(array, start, mid, &left_s_idx, &left_e_idx);
	rightMaxsum = Algorithm1(array, mid + 1, end, &right_s_idx, &right_e_idx);
	int crossMaxsum, leftSubsum = 0, rightSubsum = 0, MaxleftSubsum, MaxrightSubsum;
	MaxleftSubsum = INT_MIN;
	MaxrightSubsum = INT_MIN;

	mid_s_idx = mid;
	for (int i = mid; i >= start; i--) {
		leftSubsum += array[i];
		if (leftSubsum > MaxleftSubsum) {
			MaxleftSubsum = leftSubsum;
			mid_s_idx = i;
		}
	}

	mid_e_idx = mid + 1;
	for (int i = mid + 1; i <= end; i++) {
		rightSubsum += array[i];
		if (rightSubsum > MaxrightSubsum) {
			MaxrightSubsum = rightSubsum;
			mid_e_idx = i;
		}
	}
	crossMaxsum = MaxleftSubsum + MaxrightSubsum;
//	printf("start: %d, mid: %d, end: %d\n", start, mid, end);
//	printf("leftmaxsum: %d\nrightmaxsum: %d\ncrossmaxsum: %d\n", leftMaxsum, rightMaxsum, crossMaxsum);
//	printf("*****결론: %d*****\n\n", find_max(leftMaxsum, rightMaxsum, crossMaxsum, &which));
	int r = find_max(leftMaxsum, rightMaxsum, crossMaxsum, &which);
	if (which == 0) {
		*s_idx = left_s_idx;
		*e_idx = left_e_idx;
	}
	else if (which == 1) {
		*s_idx = right_s_idx;
		*e_idx = right_e_idx;
	}
	else if (which == 2) {
		*s_idx = mid_s_idx;
		*e_idx = mid_e_idx;
	}
	else {
		printf("error\n");
	}

//	printf("start_idx: %d, end_idx: %d\n", *s_idx, *e_idx);

	return find_max(leftMaxsum, rightMaxsum, crossMaxsum, &which);
}

//Algorithm2. 1D, Kadane's algorithm을 이용한 방법(Dynamic programming)
int Algorithm2(int* arr, int *start, int *finish, int n) {
	int currentSum = 0, maxSum = INT_MIN;
	*finish = -1;
	int local_start = 0;
	for (int i = 0; i < n; ++i) {
		currentSum += arr[i];
		if (currentSum < 0) {
			currentSum = 0; local_start = i + 1;
		}
		else if (currentSum > maxSum) {
			maxSum = currentSum;
			*start = local_start; *finish = i;
		}
	}
/*	if (*finish != -1) return maxSum;
	maxSum = arr[0];
	*start = 0;
	*finish = 0;
	for (int i = 1; i < n; i++) {
		if (arr[i] > maxSum) {
			maxSum = arr[i];
			*start = i;
			*finish = i;
		}
	}*/
	if (*finish == -1) {
		maxSum = arr[0];
		*start = 0;
		*finish = 0;
		for (int i = 1; i < n; i++) {
			if (arr[i] > maxSum) {
				maxSum = arr[i];
				*start = i;
				*finish = i;
			}
		}
	}
	return maxSum;
}

//Algorithm3. 2D, Summed Area Table
int Algorithm3(int** matrix, int *idx_i, int *idx_j, int *idx_k, int *idx_l, int n) {
	int **SummedAreaTable;
	SummedAreaTable = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++) {
		SummedAreaTable[i] = (int*)malloc(sizeof(int)*n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			SummedAreaTable[i][j] = 0;
		}
	}

	//SummedAreaTable의 1열, 1행에 값 채우기
	SummedAreaTable[0][0] = matrix[0][0];
	for (int i = 1; i < n; i++) {
		SummedAreaTable[0][i] = SummedAreaTable[0][i - 1] + matrix[0][i];
		SummedAreaTable[i][0] = SummedAreaTable[i - 1][0] + matrix[i][0];
	}
	//SummedAreaTable의 모든 값 채우기
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			SummedAreaTable[i][j] = SummedAreaTable[i - 1][j] + SummedAreaTable[i][j - 1] - SummedAreaTable[i - 1][j - 1];
			SummedAreaTable[i][j] += matrix[i][j];
		}
	}
	//sum이 가장 큰 subrectangle 구하기
	int maxSum = INT_MIN;
	int currentSum = 0;
//	int idx_i, idx_j, idx_k, idx_l;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) {
				for (int l = k; l < n; l++) {
					if ((i > 0) && (k > 0)) {
						currentSum = SummedAreaTable[l][j];
						currentSum -= SummedAreaTable[k - 1][j];
						currentSum -= SummedAreaTable[l][i - 1];
						currentSum += SummedAreaTable[k - 1][i - 1];
						/*	if (currentSum > maxSum) {
								maxSum = currentSum;
								idx_i = i;
								idx_j = j;
								idx_k = k;
								idx_l = l;
							}*/
					}
					else if ((i > 0) && (k == 0)) {
						//1행(맨 위 가로줄)
						currentSum = SummedAreaTable[l][j];
						currentSum -= SummedAreaTable[l][i - 1];
					}
					else if ((i == 0) && (k > 0)) {
						//1열(맨 왼쪽 세로줄)
						currentSum = SummedAreaTable[l][j];
						currentSum -= SummedAreaTable[k - 1][j];
					}
					else if ((i == 0) && (k == 0)) {
						currentSum = SummedAreaTable[l][j];
					}
					if (currentSum > maxSum) {
						maxSum = currentSum;
						*idx_i = i;
						*idx_j = j;
						*idx_k = k;
						*idx_l = l;
					}
				}
			}
		}
	}
	return maxSum;
}

//Algorithm4. 2D, Algorithm1을 활용한 방법
int Algorithm4(int** matrix, int *idx_i, int *idx_j, int *idx_k, int *idx_l, int n) {
	int maxSum = INT_MIN;
	int currentSum = 0;
	int *temp;
	temp = (int*)malloc(sizeof(int)*n);


	int s_idx = 0;
	int e_idx = 0;

	//i열부터 j열까지의 합을 담는 배열 temp
	//temp[k]에는 k행의 i~j열까지의 합이 담겨있다.
	for (int i = 0; i < n; i++) {
		for (int l = 0; l < n; l++) temp[l] = 0;
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) {
				temp[k] += matrix[k][j];
			}
			currentSum = Algorithm1(temp, 0, n - 1, &s_idx, &e_idx);
			if (currentSum > maxSum) {
				maxSum = currentSum;
				*idx_i = i;
				*idx_j = j;
				*idx_k = s_idx;
				*idx_l = e_idx;
			}
		}
	}
	return maxSum;
}

//Algorithm5. 2D, Algorithm2를 활용한 방법
int Algorithm5(int** matrix, int *idx_i, int *idx_j, int *idx_k, int *idx_l, int n) {
	int maxSum = INT_MIN;
	int currentSum = 0;
	int *temp;
	temp = (int*)malloc(sizeof(int)*n);
	int start = 0, finish = 0;
	//i열부터 j열까지의 합을 담는 배열 temp
	//temp[k]에는 k행의 i~j열까지의 합이 담겨있다.
	for (int i = 0; i < n; i++) {
		for (int l = 0; l < n; l++) temp[l] = 0;
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) {
				temp[k] += matrix[k][j];
			}
			currentSum = Algorithm2(temp, &start, &finish, n);
			if (currentSum > maxSum) {
				maxSum = currentSum;
				*idx_i = i;
				*idx_j = j;
				*idx_k = start;
				*idx_l = finish;
			}
		}
	}
	return maxSum;
}