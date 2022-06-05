#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<termios.h>
#include<unistd.h>
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"

/* 퍼즐게임판 크기 */
#define size 4

/* 게임 생명 카운트 */
#define life_count 100

/* 게임 종료 조건 */
int game_over;

/**********************************************************

  * size가 4일때 테스트 케이스 3개 입니다. 
 	답은 ANS 옆에 있는 커맨드를 순서대로 입력하시면 됩니다.

***********************************************************/
void Test_one(int puzzle[][4]) { //ANS : W W A A A
	puzzle[0][0] = 15;	puzzle[0][1] = 14;	puzzle[0][2] = 13;	puzzle[0][3] = 12;
	puzzle[1][0] = 0;	puzzle[1][1] = 10;	puzzle[1][2] = 9;	puzzle[1][3] = 8;
	puzzle[2][0] = 11;	puzzle[2][1] = 6;	puzzle[2][2] = 5;	puzzle[2][3] = 4;
	puzzle[3][0] = 7;	puzzle[3][1] = 3;	puzzle[3][2] = 2;	puzzle[3][3] = 1;
}
void Test_two(int puzzle[][4]) { //ANS : W A W D D W A A 
	puzzle[0][0] = 15;	puzzle[0][1] = 14;	puzzle[0][2] = 0;	puzzle[0][3] = 12;
	puzzle[1][0] = 11;	puzzle[1][1] = 10;	puzzle[1][2] = 13;	puzzle[1][3] = 9;
	puzzle[2][0] = 7;	puzzle[2][1] = 5;	puzzle[2][2] = 4;	puzzle[2][3] = 8;
	puzzle[3][0] = 3;	puzzle[3][1] = 6;	puzzle[3][2] = 2;	puzzle[3][3] = 1;
}
void Test_three(int puzzle[][4]) { //ANS : A S S D W A S D W A A W W A 
	puzzle[0][0] = 11;	puzzle[0][1] = 15;	puzzle[0][2] = 13;	puzzle[0][3] = 12;
	puzzle[1][0] = 14;	puzzle[1][1] = 6;	puzzle[1][2] = 10;	puzzle[1][3] = 8;
	puzzle[2][0] = 0;	puzzle[2][1] = 7;	puzzle[2][2] = 9;	puzzle[2][3] = 4;
	puzzle[3][0] = 3;	puzzle[3][1] = 2;	puzzle[3][2] = 5;	puzzle[3][3] = 1;
}


/**********************************************************
* 퍼즐게임의 global 변수와 게임판을 초기화 해준다.
  빈칸의 경우 0으로 초기화 해준다.
* input 	: (int [][]) 퍼즐게임판
* return 	: none
***********************************************************/
void init(int puzzle[][size])
{
    int i,j;
    game_over = 0;
    for(i = 0; i < size; i++)
    {
        for(j=0; j<size; j++)
            puzzle[i][j] = size*size-1-size*i-j;
    }
}

/**********************************************************
* 퍼즐게임판을 출력해준다.
* input 	: (int [][]) 퍼즐게임판
* return 	: none
***********************************************************/
void printPuzzle(int puzzle[][size])
{
    int i,j;
    system("clear");
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
            printf("+--");
        printf("+\n");
        for(j=0;j<size-1;j++)
            if(puzzle[i][j] == 0)
                printf("|  ");
            else    
                printf("|"ANSI_YELLOW"%2d"ANSI_RESET,puzzle[i][j]);
        if(puzzle[i][j] == 0)
            printf("|  |\n");
        else
            printf("|"ANSI_YELLOW"%2d"ANSI_RESET"|\n",puzzle[i][j]);
    }
    for(j=0;j<size;j++)
        printf("+--");
    printf("+\n");
}


/**********************************************************
* 퍼즐게임이 clear되었는지 체크한다.
* input 	: (int [][]) 퍼즐게임판			TODO
* return 	: none
***********************************************************/
void checkPuzzle(int puzzle[][size]) 
{
	int i,j;
	int n=0;
	int count=0;

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			n = size*size - (size*i+j+1);
			if (puzzle[i][j] == n)
				count+=1;}}

	if (count == size*size)
		game_over=1;}

/**********************************************************
* 퍼즐게임판에서 빈칸의 위치를 찾는다.
* input 	: (int [][]) 퍼즐게임판		TODO
* return 	: (int) 빈칸의 위치
***********************************************************/
int find_0_loc(int puzzle[][size])
{
	int i,j;
	int order=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			order++;
			if (puzzle[i][j] == 0)
				return order;}}
			
}

/**********************************************************
* 콘솔창에 입력하는 key의 값을 받아온다.(Enter 필요없음)
* input 	: none
* return 	: (int) 입력받은 key
***********************************************************/
int getch(void)
{
    char   ch;
    int   error;
    static struct termios Otty, Ntty;

    fflush(stdout);
    tcgetattr(0, &Otty);
    Ntty = Otty;
    Ntty.c_iflag = 0;
    Ntty.c_oflag = 0;
    Ntty.c_lflag &= ~ICANON;
#if 1
    Ntty.c_lflag &= ~ECHO;
#else
    Ntty.c_lflag |= ECHO;
#endif
    Ntty.c_cc[VMIN] = 0;
    Ntty.c_cc[VTIME] = 1;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

    if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
    {
	error = read(0, &ch, 1);
	error += tcsetattr(0, FLAG, &Otty);
    }

    return (error == 1 ? (int)ch : -1);
}

/**********************************************************
* command에 대한 동작을 수행한다.
  'w' 'W' - 빈칸을 아래로
  'a' 'A' - 빈칸을 오른쪽으로 
  's' 'S' - 빈칸을 위로
  'd' 'D' - 빈칸을 왼쪽으로
* input 	: (int [][]) 퍼즐게임판					TODO
			  (int) 퍼즐게임판에서 빈칸의 위치
			  (int) 입력받은 key에 대한 command
* return 	: (int) command에 대한 동작 수행여부
***********************************************************/
int move_to(int puzzle[][size],int loc,int command)
{
	int i,j;

	switch(command){
		case 0: for(i=0;i<size;i++){					//아래로
					for(j=0;j<size;j++){
						if (size*i+j+1 == loc){
							if (i<size-1){
								int temp = puzzle[i][j];
								puzzle[i][j] = puzzle[i+1][j];
								puzzle[i+1][j] = temp;
								return 1;}
							else
								return 0;
								}}}
				

		case 1: for(i=0;i<size;i++){					//오른쪽으로
					for(j=0;j<size;j++){
						if (size*i+j+1 == loc){
							if (j<size-1){
								int temp = puzzle[i][j];
								puzzle[i][j] = puzzle[i][j+1];
								puzzle[i][j+1] = temp;
								return 1;}
							else
								return 0;
							}}}
						

		case 2: for(i=0;i<size;i++){					//위로
					for(j=0;j<size;j++){
						if (size*i+j+1 == loc){
							if (i>0){
								int temp = puzzle[i][j];
								puzzle[i][j] = puzzle[i-1][j];
								puzzle[i-1][j] = temp;
								return 1;}
							else
								return 0;}}}

		case 3: for(i=0;i<size;i++){					//왼쪽으로
					for(j=0;j<size;j++){
						if (size*i+j+1 == loc){
							if (j>0){
								int temp = puzzle[i][j];
								puzzle[i][j] = puzzle[i][j-1];
								puzzle[i][j-1] = temp;
								return 1;}
							else
								return 0;}}}}
	return 0;
}

/**********************************************************
* 퍼즐게임판을 랜덤하게 섞는다.
  int iter는 셔플을 시도할 횟수이다.
* input 	: (int [][]) 퍼즐게임판
* return 	: none 
***********************************************************/
void shuffle(int puzzle[][size])
{
    int r,l;
    int iter = 100;     /* 필요시횟수를 변경해 가면서 테스트 해보세요 */
    while(iter)
    {
        iter--;
        l = find_0_loc(puzzle);
        r = rand()%4;
        move_to(puzzle,l,r);
    }
}

/**********************************************************
* getch()함수로 입력받은  key를 가져와 해당하는 key 값을 return 해준다.
  'w', 'W', 'a', 'A', 's', 'S', 'd', 'D' key를 제외한 다른 key가 입력으로 들어올시 -1을 return 한다.
* input 	: none
* return 	: (int) getch()로 입력받은 key의 값
***********************************************************/
int GetCommand() {
    int ch = getch();

    switch (ch)
    {
	case 'w':
	case 'W': return 0;
	case 'a':
	case 'A': return 1;
	case 's':
	case 'S': return 2;
	case 'd':
	case 'D': return 3;
	default: return -1;
    }

    return -1;
}

/**********************************************************
* 퍼즐게임 시작시 실행되며, 퍼즐게임판을 초기화하고,
  입력받은 command에 대한 동작을 수행한다.
  life가 0이 되거나, 게임을 clear했을 시 프로그램을 종료한다.

* input 	: none
* return 	: 0
***********************************************************/
int main(void)
{
    int puzzle[size][size]; /* 크기가 size * size인 퍼즐게임판*/
    int life = life_count; /* 게임 생명 카운트 */ 
	int command = -1;
	// 필요한 변수는 자유롭게 추가 가능

	srand(time(NULL));		/* 난수를 생성하기 위한 설정 */
    init(puzzle);			/* 퍼즐게임판 초기화 */
    shuffle(puzzle);		/* 퍼즐게임판 섞기 */
    
	//Test_one(puzzle);     /* ppt에 나와있는 test case */ 
	//Test_two(puzzle);     /* shuffle이 완성되기전 사용 */
	//Test_three(puzzle); 
	

	while(!game_over)
    {  
		/*
			입력이 일어날때마다 퍼즐게임판을 새롭게 그린다.			
		*/
        
		command = GetCommand();

		/*
		   TODO LIST

		   퍼즐게임판에서 빈칸을 찾는다. ( find_0_loc() )
		   key에 대한 동작을 수행한다.
		*/
		int loc=0;
		loc = find_0_loc(puzzle);
		int m=0;
		m = move_to(puzzle, loc, command);

		if (command != -1 && m!=0)
			life--;

        printPuzzle(puzzle); /* 퍼즐게임판 그리기 */
		printf(ANSI_GREEN"up    : w\nleft  : a\ndown  : s\nright : d\n"ANSI_RESET); 
        printf(ANSI_YELLOW"Life : %d\n"ANSI_RESET,life);
//        printf(ANSI_YELLOW"Command : %d\n"ANSI_RESET,command);
//        printf(ANSI_YELLOW"loc : %d\n"ANSI_RESET,loc);
        printf(ANSI_RED"Press Command...\n"ANSI_RESET); 
		
		/*
			TODO LIST

			퍼즐게임의 종료 조건을 체크한다.
		*/
		if (life > 0)
			checkPuzzle(puzzle);

		if (life == 0){
			checkPuzzle(puzzle);
			if (game_over == 0)
				break;}

//		if (life < 0)
//			break;
	}

    /*
		퍼즐게임 결과 출력
	*/
    printf("\n\n\n\n\n");
//	printf("life: %d\n", life);
	if(game_over)	//game_over=1, life>=0
        printf(ANSI_RED"      Success!\n\n\n"ANSI_RESET);
	else
		if(life <=0)	//game_over=0, life<=0
        	printf(ANSI_RED"      Fail!\n\n\n"ANSI_RESET);
    	else 			//game_over=0, life>0
       		printf(ANSI_RED"      Success!\n\n\n"ANSI_RESET);

    return 0;
}
