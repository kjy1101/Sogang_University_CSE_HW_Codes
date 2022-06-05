#include "tetris.h"

static struct sigaction act, oact;
int highest_score=0;

int main(){
	int exit=0;
	createRankList();
	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	Root = (Node*)malloc(sizeof(Node));
	Root->level=0;
	Root->accumulatedScore=0;
	
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			Root->recField[i][j] = field[i][j];
		}
	}
	
	Root->childsize = 40;
	Root->child = (Node**)malloc(sizeof(Node*)*Root->childsize);
	for(int a=0;a<Root->childsize;a++) {
			Root->child[a]=0;
	}
	Root->curBlockID = nextBlock[0];
	Root->parent = NULL;
	Root->recBlockX = 0;
	Root->recBlockY = 0;
	Root->recBlockRotate = 0;

	recRoot=(RecNode*)malloc(sizeof(RecNode));

	recommend(Root);
	highest_score=0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
	DrawBox(9,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(15,WIDTH+10);
	printw("SCORE");
	DrawBox(16,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(17,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}

	for( i = 0; i < 4; i++){
		move(10+i, WIDTH+13);
		for( j = 0; j < 4; j++){
			if( block[nextBlock[2]][0][i][j] == 1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
//	addch(ACS_ULCORNER);
	addch('o');
	for(i=0;i<width;i++)
//		addch(ACS_HLINE);
//	addch(ACS_URCORNER);
	addch('-');
	addch('o');
	for(j=0;j<height;j++){
		move(y+j+1,x);
//		addch(ACS_VLINE);
		addch('|');
		move(y+j+1,x+width+1);
//		addch(ACS_VLINE);
		addch('|');
	}
	move(y+j+1,x);
//	addch(ACS_LLCORNER);
	addch('o');
	for(i=0;i<width;i++)
		addch('-');
//		addch(ACS_HLINE);
//	addch(ACS_LRCORNER);
	addch('o');
}

void play(){
	int command;

	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int checkFlag = 0;
	for(int i=0;i<BLOCK_HEIGHT;i++){
		for(int j=0;j<BLOCK_WIDTH;j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				if(f[blockY+i][blockX+j]==1){
					checkFlag=1;
					break;
				}
				else if(blockY+i >= HEIGHT){
					checkFlag=1;
					break;
				}
				else if(blockX+j < 0){
					checkFlag=1;
					break;
				}
				else if(blockX+j >= WIDTH){
					checkFlag=1;
					break;
				}
			}
		}
		if(checkFlag==1) break;
	}
	if(checkFlag==1) return 0;
	else return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code

	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	//3. 새로운 블록 정보를 그린다. 
	int preY = blockY;
	int preX = blockX;
	int preR = blockRotate;
	switch(command){
		case KEY_UP:
			preR = (blockRotate+3)%4; break;
		case KEY_DOWN:
			preY = blockY - 1; break;
		case KEY_RIGHT:
			preX = blockX - 1; break;
		case KEY_LEFT:
			preX = blockX + 1; break;
	}

	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][preR][i][j]==1){
				move(i+preY+1, j+preX+1);
				printw(".");
			}
		}
	}

	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);
}

void BlockDown(int sig){
	// user code
	//강의자료 p26-27의 플로우차트를 참고한다.

	int down_ok = CheckToMove(field, nextBlock[0], blockRotate, blockY+1, blockX);
	if(down_ok==1){
		//이동 가능
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else{
		//이동 불가능
		if(blockY == -1){
			gameOver = 1;
			//움직이지 못하는데 그릴 수 있는 경우가 있고
			//움직이지 못하고 그릴 수도 없는 경우가 있다
			int lastdrawFlag=0;
			for(int a=0;a<4;a++){
				for(int b=0;b<4;b++){
					if(block[nextBlock[0]][blockRotate][a][b]==1&&field[blockY+a][blockX+b]==1) {
						lastdrawFlag=1;
						break;
					}
				}
			}
			if(lastdrawFlag==0){
				AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
				DrawField();
			}
			else{
				//lastdrawFlag==1, 그리지 못할 때, 블록이 세번째줄부터 시작했다면
				if(nextBlock[0]==1||nextBlock[0]==2||nextBlock[0]==4||nextBlock[0]==6){
					blockY--;
					lastdrawFlag=0;	
					for(int a=0;a<4;a++){
						for(int b=0;b<4;b++){
							if(block[nextBlock[0]][blockRotate][a][b]==1&&field[blockY+a][blockX+b]==1) {
								lastdrawFlag=1;
								break;
							}
						}
					}
					if(lastdrawFlag==0){
						AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
						DrawField();
					}
				}
			}
		}
		else{
			score+=AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
			DeleteLine(field);
			nextBlock[0] = nextBlock[1];
			nextBlock[1] = nextBlock[2];
			nextBlock[2] = rand()%7;
		
			Root->curBlockID=nextBlock[0];
			recommend(Root);
			highest_score=0;

			blockRotate = 0;
			blockY = -1;
			blockX = (WIDTH/2)-2;
			DrawNextBlock(nextBlock);
			DrawField();
		}
	}
	alarm(1);
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	//Block이 추가된 영역의 필드값을 바꾼다.	
	int touched=0, newscore=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(blockY+i+1<HEIGHT){
				if(block[currentBlock][blockRotate][i][j]==1 && f[blockY+i+1][blockX+j]==1){
						touched++;
				}
			}
			else{
				if(block[currentBlock][blockRotate][i][j]==1) touched++;
			}
		}
	}
	newscore += (touched * 10);

	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				field[blockY+i][blockX+j]=1;
			}
		}
	}
	return newscore;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
	int scoreFlag=0;
	int deleted_line=0;
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(f[i][j]==0){
				scoreFlag=1;
				break;
			}
		}
		if(scoreFlag==0){
			deleted_line++;
			for(int k=i-1;k>=0;k--){
				for(int l=0;l<WIDTH;l++){
					f[k+1][l]=f[k][l];
				}
			}
		}
		scoreFlag=0;
	}

	score += (deleted_line*deleted_line)*100;
	PrintScore(score);
	DrawField();
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// user code
	int shadowY = -1;
	while(1){
		shadowY++;
		if(CheckToMove(field, blockID, blockRotate, shadowY, x)==0) break;
	}
	shadowY--;
	DrawBlock(shadowY, x, blockID, blockRotate, '/');
}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
	//user code
	DrawField();
	DrawBlock(y, x, blockID, blockRotate, ' ');
	DrawShadow(y, x, blockID, blockRotate);
	DrawRecommend(recRoot->recBlockY, recRoot->recBlockX, recRoot->curBlockID, recRoot->recBlockRotate);
}

void createRankList(){
	// user code
	FILE *fp = fopen("rank.txt", "r");
	char L_name[NAMELEN];
	int L_score;
	int rank_num;
	head = malloc(sizeof(rankNode));
	head->link=NULL;

	if(fp == NULL){
		fp = fopen("rank.txt", "w");
		fprintf(fp, "0\n");
		head->score = 0;
	}
	else{
		fscanf(fp, "%d", &rank_num);
		head->score = rank_num;
		while(1){
			fscanf(fp, "%s %d", L_name, &L_score);
			if(feof(fp)) break;
			rankNode *newnode;
			newnode = malloc(sizeof(rankNode));
			strcpy(newnode->name, L_name);
			newnode->score = L_score;
			
			rankNode *curr;
			curr=head;
			while(1){
				if(curr->link==NULL) break;
				curr = curr->link;
			}

			newnode->link=curr->link;
			curr->link=newnode;
		}
	}
	fclose(fp);
}

void rank(){
	// user code
	int mode, X=0, Y=0;
	clear();
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	mode = wgetch(stdscr);

	echo();
	switch(mode){
		case '1':
			printw("X: ");
			scanw("%d", &X);

			printw("Y: ");
			scanw("%d", &Y);

			if(X=='\0') X=1;
			if(Y=='\0') Y=head->score;

			int flag=0;
			if(Y > head->score){
				Y=head->score;
				flag=1;
			}

			int flag2=0;
			if(X < 1){
				X=1;
				flag2=1;
			}

			printw("        name         | score\n");
			printw("-------------------------------\n");
			if(X>Y){
				printw("\nsearch failure: no rank in the list\n");
			}
			else{
				int count=0;
				rankNode *curr;
				rankNode *prev;
				curr=head;
				while(1){
					count++;
					prev=curr;
					curr=curr->link;
					if(count >= X && Y >= count){
						printw(" %-20s", curr->name);
						printw("| %d\n", curr->score);
					}
					else{
						if(count > Y || curr->link == NULL) break;
					}
				}
				if(flag2==1) printw("\nRanks start from #1.\n");
				if(flag==1) printw("\nThere are only %d ranks.\n", head->score);
			}

			break;
		case '2':{
			char search_name[NAMELEN];
			int flag=0;
			printw("input the name: ");
			scanw("%s", search_name);

			rankNode *curr;
			curr=head;
			printw("        name         | score\n");
			printw("-------------------------------\n");
			while(1){
				if(curr->link==NULL) break;
				curr=curr->link;
				if(strcmp(search_name, curr->name)==0){
					printw("%-20s | %d\n", curr->name, curr->score);
					flag=1;
				}
			}
			if(flag==0) printw("\nsearch failure: no name in the list\n");

			break;}
		case '3':{
			int del_rank;
			printw("input the rank: ");
			scanw("%d", &del_rank);

			if(del_rank >= 1 && del_rank <= head->score){
				int flag=0;
				rankNode *curr;
				curr=head;
				int count=0;
				while(1){
					if(curr->link==NULL) break;
					if(del_rank==1){
						flag=1;
						break;
					}
					curr=curr->link;
					count++;
					if(count==del_rank-1 && del_rank > 1){
						flag=1;
						break;
					}
				}
				if(flag==1){
					rankNode *delete_node;
					delete_node = curr->link;
					curr->link = curr->link->link;
					(head->score)--;
					writeRankFile();
					free(delete_node);
					printw("\nresult: the rank deleted\n");
				}
			}
			else{
				printw("\nsearch failure: the rank not in the list\n");
			}
			break;}
	}
	
	noecho();
	getch();
}

void writeRankFile(){
	// user code
	FILE *fp = fopen("rank.txt", "w");
	fprintf(fp, "%d\n", head->score);
	rankNode *curr;
	curr=head->link;
	for(int i=0;i<head->score;i++){
		fprintf(fp, "%s %d\n", curr->name, curr->score);
		curr=curr->link;
	}
	fclose(fp);
}

void newRank(int score){
	// user code
	clear();
	echo();
	char your_name[NAMELEN];
	printw("your name: ");
	scanw("%s", your_name);
	rankNode *newnode;
	newnode = malloc(sizeof(rankNode));
	strcpy(newnode->name, your_name);
	newnode->score = score;

	rankNode *curr;
	curr=head;
	while(1){
		if(curr->link==NULL || ((curr->link->score) < newnode->score)) break;
		curr=curr->link;
	}

	newnode->link = curr->link;
	curr->link = newnode;
	(head->score)++;
	writeRankFile();
	noecho();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
	DrawBlock(y,x,blockID, blockRotate, 'R');
}

int recommend(Node *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수
	int p_rotate=0;
	int p_position[7][4]={0};
	switch(root->curBlockID){
		case 0: {p_rotate=2;
				p_position[0][0]=7; p_position[0][1]=10;
				break;}
		case 1: {p_rotate=4;
				p_position[1][0]=8; p_position[1][1]=9;
				p_position[1][2]=8; p_position[1][3]=9;
				break;}
		case 2: {p_rotate=4;
				p_position[2][0]=8; p_position[2][1]=9;
				p_position[2][2]=8; p_position[2][3]=9;
				break;}
		case 3: {p_rotate=4;
				p_position[3][0]=8; p_position[3][1]=9;
				p_position[3][2]=8; p_position[3][3]=9;
				break;}
		case 4: {p_rotate=1;
				p_position[4][0]=9;
				break;}
		case 5: {p_rotate=2;
				p_position[5][0]=8; p_position[5][1]=9;
				break;}
		case 6: {p_rotate=2;
				p_position[6][0]=8; p_position[6][1]=9;
				break;}
	}
	int seq=0;
	for(int i=0;i<p_rotate;i++){
		for(int j=0;j<p_position[root->curBlockID][i];j++){
			//새 노드를 만들고 parent에 연결
			Node* treenode;
			treenode = (Node*)malloc(sizeof(Node));
			root->child[seq] = treenode;
			seq++;
			//레벨
			treenode->level = (root->level) + 1;
			//누적점수(추가 계산 필요)
			treenode->accumulatedScore = root->accumulatedScore;
			//부모 노드 연결
			treenode->parent = root;
			//자식 노드 할당
			if(treenode->level < VISIBLE_BLOCKS){
				treenode->childsize = 40;
				treenode->child = (Node**)malloc(sizeof(Node*)*(treenode->childsize));
				for(int k=0;k<(treenode->childsize);k++){
					treenode->child[k] = 0;//(Node*)malloc(sizeof(Node));
					//treenode->child[k] = (Node*)malloc(sizeof(Node));
				}
			}
			else{
				treenode->child = NULL;
			}
			//블록 ID(다음레벨에서 사용할 블록)
			if(treenode->level < VISIBLE_BLOCKS) treenode->curBlockID = nextBlock[treenode->level];
			//추천할 X좌표
			switch(root->curBlockID){
				case 0:{if(i==0) treenode->recBlockX=j;
						else treenode->recBlockX=j-1;
						break;}
				case 1:{if(i==1) treenode->recBlockX=j-2;
						else treenode->recBlockX=j-1;
						break;}
				case 2:{if(i==1) treenode->recBlockX=j-2;
					    else treenode->recBlockX=j-1;
					    break;}
				case 3:{if(i==3) treenode->recBlockX=j-1;
					    else treenode->recBlockX=j;
					    break;}
				case 4:{treenode->recBlockX=j-1;
					   break;}
				case 5:{treenode->recBlockX=j-1;
					   break;}
				case 6:{treenode->recBlockX=j-1;
					   break;}
			}
			//추천할 회전수
			treenode->recBlockRotate = i;
			//추천할 Y좌표
			int recY=-1, temp=0;
			while(1){
				if(treenode->level==1) temp = CheckToMove(field, root->curBlockID, i, recY+1, treenode->recBlockX);
				else temp = CheckToMove(root->recField, root->curBlockID, i, recY+1, treenode->recBlockX);
				if(temp==1) recY++;
				else break;
			}
			treenode->recBlockY = recY;
			//필드
			for(int k=0;k<HEIGHT;k++){
				for(int l=0;l<WIDTH;l++){
					if(treenode->level==1){
						treenode->recField[k][l] = field[k][l];
					}
					else{
						treenode->recField[k][l] = root->recField[k][l];
					}
				}
			}
			//누적점수 계산(면적), 현재 treenode의 recField는 field와 동일
			int touched=0;
			for(int k=0;k<BLOCK_HEIGHT;k++){
				for(int l=0;l<BLOCK_WIDTH;l++){
					if((treenode->recBlockY)+k+1<HEIGHT){
						if((block[root->curBlockID][i][k][l]==1) && (treenode->recField[(treenode->recBlockY)+k+1][(treenode->recBlockX)+l]==1)) touched++;
					}
					else{
						if(block[root->curBlockID][i][k][l]==1) touched++;
					}
				}
			}
			treenode->accumulatedScore += (touched*10);
			//필드 정보 변경
			for(int k=0;k<BLOCK_HEIGHT;k++){
				for(int l=0;l<BLOCK_WIDTH;l++){
					if(block[root->curBlockID][i][k][l]==1)
						treenode->recField[recY+k][(treenode->recBlockX)+l]=1;
				}
			}
			//누적점수계산(지워지는 줄)
			int scoreFlag=0, del_line=0;
			for(int k=0;k<HEIGHT;k++){
				for(int l=0;l<WIDTH;l++){
					if(treenode->recField[k][l]==0){
						scoreFlag=1;
						break;
					}
				}
				if(scoreFlag==0){
					del_line++;
					for(int a=k-1;a>=0;a--){
						for(int b=0;b<WIDTH;b++){
							treenode->recField[a+1][b]=treenode->recField[a][b];
						}
					}
				}
				scoreFlag=0;
			}
			treenode->accumulatedScore += (del_line*del_line)*100;

			//시작
			if(treenode->level < VISIBLE_BLOCKS){
				recommend(treenode);
			}
			else{
				if(treenode->accumulatedScore > highest_score){
					highest_score = treenode->accumulatedScore;
					if(VISIBLE_BLOCKS == 3){
						recRoot->curBlockID = treenode->parent->parent->parent->curBlockID;
						recRoot->score = treenode->parent->parent->accumulatedScore;
						recRoot->recBlockX = treenode->parent->parent->recBlockX;
						recRoot->recBlockY = treenode->parent->parent->recBlockY;
						recRoot->recBlockRotate = treenode->parent->parent->recBlockRotate;
					}
					else if(VISIBLE_BLOCKS == 2){
						recRoot->curBlockID = treenode->parent->parent->curBlockID;
						recRoot->score = treenode->parent->accumulatedScore;
						recRoot->recBlockX = treenode->parent->recBlockX;
						recRoot->recBlockY = treenode->parent->recBlockY;
						recRoot->recBlockRotate = treenode->parent->recBlockRotate;
					}
					else if(VISIBLE_BLOCKS == 1){
						recRoot->curBlockID = treenode->parent->curBlockID;
						recRoot->score = treenode->accumulatedScore;
						recRoot->recBlockX = treenode->recBlockX;
						recRoot->recBlockY = treenode->recBlockY;
						recRoot->recBlockRotate = treenode->recBlockRotate;
					}
				}
			}
			free(treenode);
		}
	}
	// user code
	return max;
}

void recommendedPlay(){
	// user code
}


