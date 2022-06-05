#include <stdio.h>
#include <stdlib.h>

int find_max(int a, int b, int c, int *dir);
void print_path(int** path, int r, int l);
void print_path2(int** path, int r, int l, int total);
int xgap = 0, ygap = 0, xidx = 0, yidx = 0;
int xgap2 = 0, ygap2 = 0;
int xgap_location[20000];
int ygap_location[20000];

int main(void) {
	//input.txt에서 입력bin파일 이름, 사전설정된 s,f,p 읽기
	FILE *fp1;
	fp1 = fopen("input.txt", "r");
	if (fp1 == NULL) {
		printf("File open error.\n");
		return;
	}
	char filename[32];
	int s, f, p; //s:두 문자가 일치할때(+), f:두 문자가 다를때(-), p:gap의 개수(-)
	fscanf(fp1, "%s %d %d %d", filename, &s, &f, &p);
	fclose(fp1);
	
	//입력bin파일 열기
	FILE *fp;
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("File open error.\n");
		return;
	}
	int lengthX = 0, lengthY = 0;
	fread(&lengthX, sizeof(int), 1, fp);
	fread(&lengthY, sizeof(int), 1, fp);
	char X[10000] = { 0 }, Y[10000] = { 0 };
	int i, j;
	for (i = 0; i < lengthX; i++) fread(&X[i], sizeof(char), 1, fp);
	for (i = 0; i < lengthY; i++) fread(&Y[i], sizeof(char), 1, fp);
	fclose(fp);	
	
//	printf("지금 연 파일의 이름은 %s\n", filename);
//	printf("s:%d, f:%d, p:%d\n", s, f, p);
//	printf("문자열 X의 길이는 %d\n", lengthX);
//	printf("문자열 X의 내용은 %s\n", X);
//	printf("문자열 Y의 길이는 %d\n", lengthY);
//	printf("문자열 Y의 내용은 %s\n", Y);
	

	//알고리즘 시작
	//table S 채우기
	int **S; //점수계산
	S = (int**)malloc(sizeof(int*)*(lengthX + 1));
	for (i = 0; i <= lengthX; i++) S[i] = (int*)malloc(sizeof(int)*(lengthY + 1));
	
	int **Path; //경로
	Path = (int**)malloc(sizeof(int*)*(lengthX + 1));
	for (i = 0; i <= lengthX; i++) Path[i] = (int*)malloc(sizeof(int)*(lengthY + 1));

	for (i = 0; i <= lengthX; i++) {
		S[i][0] = p * i*-1;
		Path[i][0] = -1;
	}
	for (i = 0; i <= lengthY; i++) {
		S[0][i] = p * i*-1;
		Path[0][i] = -1;
	}
	//0:↖, 1:↑(Y에 gap 삽입), 2:←(X에 gap 삽입)
	int sc = 0; int dir = -1;
	for (i = 1; i <= lengthX; i++) {
		for (j = 1; j <= lengthY; j++) {
			if (X[i-1] == Y[j-1]) sc = s;
			else sc = f * -1;
			S[i][j] = find_max(S[i - 1][j - 1] + sc, S[i][j - 1] - p, S[i - 1][j] - p, &dir);
			Path[i][j] = dir;
		}
	}

/*	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%d ", S[i][j]);
		}
		printf("\n");
	}*/
	
/*	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			if (Path[i][j] == 0) printf("↖ ");
			else if (Path[i][j] == 1) printf("↑ ");
			else if (Path[i][j] == 2) printf("← ");
			else printf("0 ");
			printf("%d ", Path[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/
	print_path(Path, lengthX, lengthY);
//	xgap_location = (int*)malloc(sizeof(int)*xgap);
//	ygap_location = (int*)malloc(sizeof(int)*ygap);
	print_path2(Path, lengthX, lengthY, lengthX + xgap);

	FILE *outfp;
	outfp = fopen("output.txt", "w");
	fprintf(outfp, "%d\n%d\n", S[lengthX][lengthY], lengthX + xgap);
	fprintf(outfp, "%d\n", xgap);
	for (i = xgap - 1; i >= 0; i--) {
		fprintf(outfp, "%d\n", xgap_location[i]);
	}
	fprintf(outfp, "%d\n", ygap);
	for (i = ygap - 1; i >= 0; i--) {
		fprintf(outfp, "%d\n", ygap_location[i]);
	}
	fclose(outfp);
/*	printf("largest score is %d\n", S[lengthX][lengthY]);
	printf("full length of string is %d\n", lengthX + xgap);
	printf("xgap: %d, ygap: %d\n", xgap, ygap);
	for (i = 0; i < xgap; i++) {
		printf("%d ", xgap_location[i]);
	}
	printf("\n");
	for (i = 0; i < ygap; i++) {
		printf("%d ", ygap_location[i]);
	}
	printf("\n");*/
	return 0;
}

int find_max(int a, int b, int c, int *dir) {
	if (a >= b) {
		if (a >= c) {
			*dir = 0;
			return a;
		}
		else {
			*dir = 1;
			return c;
		}
	}
	else{
		if (b > c) {
			*dir = 2;
			return b;
		}
		else {
			*dir = 1;
			return c;
		}
	}
}

void print_path(int** path, int r, int l) {
	if (r == 0 && l == 0) return;

	if (r == 0 && l > 0) {
	//	printf("← %d번 더\n",l);
		xgap += l; return;
	}
	if (r > 0 && l == 0) {
	//	printf("↑ %d번 더\n",r);
		ygap += r; return;
	}

	if (path[r][l] == 0) {
		//0:↖, 1:↑(Y에 gap 삽입), 2:←(X에 gap 삽입)
	//	printf("↖ ");
		print_path(path, r - 1, l - 1);
	}
	else if (path[r][l] == 1) {
	//	printf("↑ ");
		ygap++;
		print_path(path, r - 1, l);
	}
	else if(path[r][l]==2){
	//	printf("←\n");
		xgap++;
		print_path(path, r, l - 1);
	}
}

void print_path2(int** path, int r, int l, int total) {
	if (r == 0 && l == 0) return;

	if (r == 0 && l > 0) {
	//	printf("← %d번 더\n", l);
		for (int i = 0; i < l; i++) {
			xgap_location[xgap2 + i] = total--;
		}
		xgap2 += l; return;
	}
	if (r > 0 && l == 0) {
	//	printf("↑ %d번 더\n", r);
		for (int i = 0; i < r; i++) {
			ygap_location[ygap2 + i] = total--;
		}
		ygap2 += r; return;
	}

	if (path[r][l] == 0) {
		//0:↖, 1:↑(Y에 gap 삽입), 2:←(X에 gap 삽입)
	//	printf("↖ ");
		print_path2(path, r - 1, l - 1,total-1);
	}
	else if (path[r][l] == 1) {
	//	printf("↑ ");
		ygap_location[ygap2] = total;
		ygap2++;
		print_path2(path, r - 1, l,total-1);
	}
	else if (path[r][l] == 2) {
	//	printf("←\n");
		xgap_location[xgap2] = total;
		xgap2++;
		print_path2(path, r, l - 1,total-1);
	}
}