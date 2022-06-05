#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define COMMAND_MAX_LEN 100
#define MEMORY_MAX_SIZE 1024*1024	// 1 Mbyte
#define OPCODE_HASH_TABLE_SIZE 20
#define ERROR_NONE 0 				// 에러없음
#define ERROR_INVALID_INPUT 1 		// 없는 명령어
#define ERROR_ARGUMENT 2 			// 인자 관련 에러

/* 구조체 */
struct command{							// [ 명령어 ]
	char *input_full; 					// 입력받은 전체 문장
	int input_num; 						// 명령어가 몇 조각으로 나누어지는지
	char *input_piece[COMMAND_MAX_LEN]; // 명령어 쪼개놓은거 저장
	int error_type; 					// 에러의 종류, 기본값 0(에러없음)
};

struct history_node{					// [ history linkedlist ]
	struct history_node *next;			// 다음 노드를 가리킨다.
	char *command;						// 정제된 명령어
	int order;							// 순서
};

struct opcode_hash_table_node{				// [ opcode linkedlist ]
	int opcode;								// opcode 값
	char *instruction;						// 명령어
	char *format;							// 형식
	struct opcode_hash_table_node *next;	// 다음 노드를 가리킨다.
};

/* 전역변수 */
struct history_node *head;											// history LinkedList의 head node
void *memory;														// 메모리 공간
int stored_start;													// 다음에 출력할 메모리의 시작주소
struct opcode_hash_table_node *opcode_head[OPCODE_HASH_TABLE_SIZE];	// Opcode Linkedlist의 head node

/* 함수 원형 */
void help();
void dir();
void quit();
void add_history(char *cmd);
void print_history();
void dump(int *start, int *end);
int check_valid_input_16(char *num_str); //16진수로 변환할 수 있는 인자인지 확인
void edit(int address, int value);
void fill(int start, int end, int value);
void reset();
int opocde_mnemonic(char *mnemonic);
void opcodelist();
