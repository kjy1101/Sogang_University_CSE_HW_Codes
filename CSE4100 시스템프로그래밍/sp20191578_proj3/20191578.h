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

#define ASM_WORD_MAX_LEN 30
#define SIMPLE 3
#define INDIRECT 2
#define IMMEDIATE 1

/* Project 1 */
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

/* Project 2 */
/* 구조체 */
struct asm_line {
	char* full_line;
	int line_num;
	int address;
	char* line_piece[4];
	int piece_num;
	char* label;
	char* instruction;
	char* operand;
	int format;
	int addressing_mode;
	int index;
	int opcode;
	char* obj_code;
	struct asm_line* next;
};

struct symbol{
	char* name;
	int address;
	struct symbol* next;
};

/* 전역변수 */
struct asm_line* asm_head;
struct symbol* symbol_table_head;
int starting_address;
int program_length;
int symbol_success;
int symbol_count;
struct symbol ordered_symbol[100];

/* 함수원형 */
int assemble_pass1(char* filename); //assemble fail - return 1, success - return 0;
int assemble_pass2();				//assemble fail - return 1, success - return 0;
int assemble(char* filename);		//assemble fail - return 1, success - return 0;
int search_symbol(char *symbol_name);
int search_opcode(char *opcode_name);
int search_operand(char *operand_name);
int return_opcode(char *opcode_name);
void print_asm();
int type(char *filename);
void symbol();
void symbol_print();


/* Project 3 */
/* 구조체 */
struct symtab_node{
	char control_section[10];
	char symbol_name[10];
	int address;
	int length;
};

/* 전역변수 */
int progaddr;
int csaddr;
struct symtab_node symtab[100];
int symtab_index;
int breakpoint[100];
int breakpoint_num;
int program_length;
int regA, regX, regL, regPC, regB, regS, regT, condition_code;

/* 함수원형 */
int progaddr_set(char* address);
int loader(char* filename1, char* filename2, char* filename3, int file_num);
int loader_pass1(char* filename);
int loader_pass2(char* filename);
int search_symtab(char* symbol_name);
int print_symtab();
int create_breakpoint(char* point);
int find_breakpoint(int point);
int run();

/* 파일을 읽어서 내용을 출력한다. */
int type(char *filename){
	FILE *read_fp = fopen(filename, "r");
	if(read_fp == NULL){
		printf("[ERROR] No file!\n");
		return 1;
	}
	char line[COMMAND_MAX_LEN]="\0";
	while(!feof(read_fp)){
		if(fgets(line, COMMAND_MAX_LEN, read_fp)==NULL) break;
		printf("%s", line);
	}
	fclose(read_fp);
	return 0;
}





/* Assemble Algorithm Pass1 */
int assemble_pass1(char* filename) {

	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[ERROR] No file!\n");
		return 1;
	}

	/* asm 파일 읽어서 구조체에 넣기*/
	int line_number = 5;
	struct asm_line* prev = asm_head;
	while (!feof(fp)) {
		char* line;
		line = malloc(COMMAND_MAX_LEN * sizeof(char));
		strcpy(line, "0");
		char* line2;
		line2 = malloc(COMMAND_MAX_LEN * sizeof(char));
		strcpy(line2, "0");

		if(fgets(line, COMMAND_MAX_LEN, fp)==NULL) break;

		strcpy(line2, line);
		struct asm_line* newline;
		newline = malloc(sizeof(struct asm_line));
		newline->full_line = line;
		for (int i = 0; i < 4; i++) {
			newline->line_piece[i] = malloc(sizeof(line));
			newline->line_piece[i] = NULL;
		}
		newline->label = malloc(ASM_WORD_MAX_LEN);
		newline->instruction = malloc(ASM_WORD_MAX_LEN);
		newline->operand = malloc(ASM_WORD_MAX_LEN);
		newline->line_num = line_number;
		line_number += 5;
		newline->piece_num = 0;
		newline->format = 0;
		newline->addressing_mode = 0;
		newline->index = 0;
		newline->address = -1;
		newline->opcode = -1;
		newline->obj_code = malloc(ASM_WORD_MAX_LEN);
		newline->next = NULL;


		/* 처음 쪼개서 넣기*/
		newline->line_piece[newline->piece_num] = strtok(line2, " \n");
		if (newline->line_piece[newline->piece_num] != NULL) {
			if (strcmp(newline->line_piece[newline->piece_num], ".") != 0) {
				newline->line_piece[++(newline->piece_num)] = strtok(NULL, " \n");
				newline->line_piece[++(newline->piece_num)] = strtok(NULL, "\n");
				newline->line_piece[newline->piece_num] = strtok(newline->line_piece[newline->piece_num], " ");
			}
		}


		/* Operand에 쉼표 있는 경우 조정 */
		for (int i = 0; i < 3; i++) {
			if (newline->line_piece[i] != NULL) {
				char* ptr = strchr(newline->line_piece[i], ',');
				if (ptr != NULL) {
					if(strcmp(newline->line_piece[i+1], "X")==0){
						//indexed addressing
						newline->line_piece[i] = strtok(newline->line_piece[i],",");
						newline->line_piece[i+1] = NULL;
						newline->index = 1;
					}
					else{
						strcat(newline->line_piece[i], newline->line_piece[i + 1]);
						newline->line_piece[i + 1] = NULL;
					}
				}
			}
		}
		

		/* label, opcode, operand, 주석 구분해서 정리 */
		if (newline->line_piece[0] != NULL) {
			if (strcmp(newline->line_piece[0], ".") != 0) {
				if (newline->line_piece[2] != NULL) {
					strcpy(newline->label, newline->line_piece[0]);
					strcpy(newline->instruction, newline->line_piece[1]);
					strcpy(newline->operand, newline->line_piece[2]);
					if((newline->label[0]>='0')&&(newline->label[0]<='9')){ // Label은 숫자로 시작하지 않는다.
						printf("[ERROR] Invalid label name\n");
						printf("[ERROR LINE] %s", newline->full_line);
						return 1;
					}
				}
				else {
					newline->label = NULL;
					strcpy(newline->instruction, newline->line_piece[0]);
					if (newline->line_piece[1] != NULL) {
						strcpy(newline->operand, newline->line_piece[1]);
					}
					else {
						newline->operand = NULL;
					}
				}
			}
			else {
				newline->label = NULL;
				newline->instruction = "COMMENT";
				newline->operand = NULL;
			}
		}
		else {
			newline->label = NULL;
			newline->instruction = "BLANK";
			newline->operand = NULL;
		}


		/* Opcode 앞에 +붙은 경우 +를 떼고 4형식으로 저장 */
		if(newline->instruction[0]=='+'){
			newline->instruction = strtok(newline->instruction, "+");
			newline->format = 4; // format == 4라는 건 앞에 +가 붙어있었다는 의미
		}


		/* Operand 앞에 #이나 @ 붙은 경우 떼고 addressing mode 저장 */
		if(newline->operand!=NULL){
			if(newline->operand[0]=='#'){
				newline->operand = strtok(newline->operand, "#");
				newline->addressing_mode = IMMEDIATE;
			}
			else if(newline->operand[0]=='@'){
				newline->operand = strtok(newline->operand, "@");
				newline->addressing_mode = INDIRECT;
			}
			else{
				newline->addressing_mode = SIMPLE;
			}
		}
		else{
			newline->addressing_mode = SIMPLE;
		}

		prev->next = newline;
		prev = newline;
	}
	fclose(fp);



	/* Pass1 Algorithm Start */
	int LOCCTR = 0;
	starting_address = 0;
	program_length = 0;
	struct asm_line* curr = asm_head->next;
	if (strcmp(curr->instruction, "START") == 0) {
		starting_address = strtol(curr->operand, NULL, 16);
		LOCCTR = starting_address;
		curr->address = LOCCTR;
		curr=curr->next;
	}
	while(strcmp(curr->instruction, "END")!=0){
		if(strcmp(curr->instruction, "COMMENT")!=0){
			if(curr->label != NULL){
				int label_found = search_symbol(curr->label);
				if(label_found == 0){
					/* symbol table에 이미 Label이 있다, set error flag */
					printf("[ERROR] Duplicate Symbol\n");
					printf("[ERROR LINE] %s", curr->full_line);
					return 1;
				}
				else{
					/* symbol table에 Label이 없다, 넣기 */
					struct symbol* newSymbol = malloc(sizeof(struct symbol));
					newSymbol->name = malloc(ASM_WORD_MAX_LEN);
					strcpy(newSymbol->name, curr->label);
					newSymbol->address = LOCCTR;
					newSymbol->next = symbol_table_head->next;
					symbol_table_head->next=newSymbol;
					curr->address = LOCCTR;
				}
			}

			int opcode_found = search_opcode(curr->instruction); // 반환값: format num
			if(opcode_found > 0){
				if(curr->format != 4){
					curr->format = opcode_found;
					curr->address = LOCCTR;
				}
				else{
					if(opcode_found != 3){
						printf("[ERROR] Invalid Format\n");
						printf("[ERROR LINE] %s", curr->full_line);
						return 1;
					}
					else{
						curr->address = LOCCTR;
					}
				}
				LOCCTR += curr->format;
			}
			/* instruction이 Assembler directives인 경우 */
			else if(strcmp(curr->instruction, "WORD")==0){
				LOCCTR += 3;
			}
			else if(strcmp(curr->instruction, "RESW")==0){ // 10진수
				for(unsigned int i=0;i<strlen(curr->operand);i++){
					if(curr->operand[i]<'0'||curr->operand[i]>'9'){
						printf("[ERROR] Invalid operand\n");
						printf("[ERROR LINE] %s", curr->full_line);
						return 1;
					}
				}
				int temp = strtol(curr->operand, NULL, 10);
				LOCCTR += (3*temp);
			}
			else if(strcmp(curr->instruction, "RESB")==0){ // 10진수
				for(unsigned int i=0;i<strlen(curr->operand);i++){
					if(curr->operand[i]<'0'||curr->operand[i]>'9'){
						printf("[ERROR] Invalid operand\n");
						printf("[ERROR LINE] %s", curr->full_line);
						return 1;
					}
				}
				int temp = strtol(curr->operand, NULL, 10);
				LOCCTR += temp;
			}
			else if(strcmp(curr->instruction, "BYTE")==0){
				if(curr->operand[0]=='C'){
					LOCCTR += (strlen(curr->operand)-3);
				}
				else if(curr->operand[0]=='X'){
					LOCCTR += ((strlen(curr->operand)-3)/2);
				}
			}
			else if(strcmp(curr->instruction, "BASE")==0){}
			else{
				/* 아예 유효하지 않은 Instrucion */
				printf("[ERROR] Invalid Operation\n");
				printf("[ERROR LINE] %s", curr->full_line);
				return 1;
			}
		}
		curr = curr->next;
	}
	program_length = (LOCCTR - starting_address);
	return 0;
}





/* Pass1 - SYMTAB에 처음 넣을 때 사용하는 search */
int search_symbol(char *symbol_name){
	struct symbol* curr = symbol_table_head->next;
	while(curr != NULL){
		if(strcmp(symbol_name, curr->name)==0){
			return 0; //있음
		}
		curr=curr->next;
	}
	return 1; //없음
}





/* Pass2 - SYMTAB에서 operand 찾을 때 사용하는 search */
int search_operand(char *operand_name){
	struct symbol* curr = symbol_table_head->next;
	while(curr != NULL){
		if(strcmp(operand_name, curr->name)==0){
			return curr->address; //있음, 주소값 반환
		}
		curr=curr->next;
	}
	return -1; //없음
}





/* Pass1 - opcode search하고 format 반환 */
int search_opcode(char *opcode_name){ //opcode format 반환, 없으면 -1 반환
	for(int i=0;i<OPCODE_HASH_TABLE_SIZE;i++){
		struct opcode_hash_table_node *curr = opcode_head[i]->next;
		while(curr != NULL){
			if(strcmp(opcode_name, curr->instruction) == 0){
				if(strcmp(curr->format, "1")==0){
					return 1; //format1(1byte)
				}
				else if(strcmp(curr->format, "2")==0){
					return 2; //format2(2byte)
				}
				else if(strcmp(curr->format, "3/4")==0){
					return 3;
				}
			}
			curr = curr->next;
		}
	}
	return -1; //없음
}





/* Pass2 - opcode search하고 opcode 반환 */
int return_opcode(char *opcode_name){
	for(int i=0;i<OPCODE_HASH_TABLE_SIZE;i++){
		struct opcode_hash_table_node *curr = opcode_head[i]->next;
		while(curr != NULL){
			if(strcmp(opcode_name, curr->instruction) == 0){
				return curr->opcode;
			}
			curr = curr->next;
		}
	}
	return -1;
}




/* 중간 확인용 print 함수 */
void print_asm(){
	struct asm_line* curr = asm_head->next;
	while (curr != NULL) {
		if(strcmp(curr->instruction, "COMMENT")!=0){
			printf("%3d\t", curr->line_num);
			if((curr->address > 0)||(curr->line_num<15)) printf("%04X\t", curr->address);
			else printf("\t");
			if(curr->label != NULL) printf("%s\t", curr->label);
			else printf("\t");
			if(curr->instruction != NULL) printf("%s\t", curr->instruction);
			else printf("\t");
			if(curr->operand != NULL) printf("%s\t", curr->operand);
			else printf("\t");
			if(curr->obj_code != NULL) printf("\t%s\t", curr->obj_code);
			else printf("\t\t");
			printf("\n");
		}
		else{
			printf("%03d\t", curr->line_num);
			printf("%s", curr->full_line);
		}
		curr=curr->next;
	}
	printf("Program length is %X\n", program_length);
}





/* Assemble Algorithm Pass2 */
int assemble_pass2(){

	struct asm_line* curr = asm_head->next;
	if (strcmp(curr->instruction, "START") == 0) {
		strcpy(curr->obj_code, "\0");
		curr=curr->next;
	}

	char object_code[30]="\0";
	int BASE = 0;
	while(strcmp(curr->instruction, "END")!=0){
		if(strcmp(curr->instruction, "COMMENT")!=0){
			int opcode_found = return_opcode(curr->instruction);
			if(opcode_found >= 0){
				/* opcode_found에는 opcode(숫자)가 들어있음, 양수면 Opcode table에 존재하는 instruction  */
				if(curr->format > 2){
					opcode_found += curr->addressing_mode;
				}
				sprintf(object_code, "%02X", opcode_found);

				char operand_address[30]="\0";
				if(curr->operand != NULL){
					int operand_found = search_operand(curr->operand);
					if(operand_found >= 0){
						/* SYMTAB에 operand(label) 있음 */

						if(curr->format == 4){
							sprintf(operand_address, "%05X", operand_found);
							strcat(object_code, "1");
							strcat(object_code, operand_address);
						}

						else if(curr->format == 3){
							int PC_or_BASE = 0;
							struct asm_line* PC = curr->next;
							while(PC->address == -1){
								PC = PC->next;
							}
							int address=0;
							char address_string[30]="\0";
							address = operand_found - (PC->address);
							sprintf(address_string, "%03X", address);
							if(strlen(address_string)>3){
								char last_3bit[9]="\0";
								last_3bit[strlen(address_string)-1]=address_string[strlen(address_string)-1];
								last_3bit[strlen(address_string)-2]=address_string[strlen(address_string)-2];
								last_3bit[strlen(address_string)-3]=address_string[strlen(address_string)-3];
								for(unsigned int i=0;i<(strlen(address_string)-3);i++){
									last_3bit[i]='F';
								}
								if(strcmp(address_string, last_3bit)==0){
									PC_or_BASE = 0; //PC
									strcpy(address_string, "\0");
									address_string[0]=last_3bit[5];
									address_string[1]=last_3bit[6];
									address_string[2]=last_3bit[7];
									address_string[3]='\0';
								}else{
									PC_or_BASE = 1; //BASE
								}
							}else{
								PC_or_BASE = 0; //PC
							}


							if(PC_or_BASE == 0){
								//PC
								if(curr->index == 1){
									strcat(object_code, "A");
								}
								else{
									strcat(object_code, "2");
								}
							}
							else{
								//BASE
								sprintf(address_string, "%03X", operand_found-BASE);
								if(curr->index == 1){
									strcat(object_code, "C");
								}
								else{
									strcat(object_code, "4");
								}
							}
							strcat(object_code, address_string);
						}

						else{
							sprintf(operand_address, "%X", operand_found);
							strcat(object_code, operand_address);
						}
					}
					else{
						/* SYMTAB에 일치하는 operand(label)이 없음 */
						/* Format 2, register number */
						if(curr->format == 2){
							for(unsigned int i=0;i<strlen(curr->operand);i++){
								if(curr->operand[i]=='A'){
									strcat(object_code, "0");
								}
								else if(curr->operand[i]=='X'){
									strcat(object_code, "1");
								}
								else if(curr->operand[i]=='L'){
									strcat(object_code, "2");
								}
								else if(curr->operand[i]=='B'){
									strcat(object_code, "3");
								}
								else if(curr->operand[i]=='S'){
									strcat(object_code, "4");
								}
								else if(curr->operand[i]=='T'){
									strcat(object_code, "5");
								}
								else if(curr->operand[i]=='F'){
									strcat(object_code, "6");
								}
								else if(curr->operand[i]=='P'){
									strcat(object_code, "8");
								}
							}

							if(strlen(curr->operand)==1){
								strcat(object_code, "0");
							}
						}

						/* Format 4, immediate addressing */
						else if(curr->format == 4){
							int over_dec=0;
							for(unsigned int i=0;i<strlen(curr->operand);i++){ // 10진수
								if((curr->operand[i]<'0')||(curr->operand[i]>'9')){
									over_dec=1;
								}
							}
							if(over_dec == 0){
								int temp = strtol(curr->operand, NULL, 10);
								sprintf(operand_address, "%05X", temp);
								strcat(object_code, "1");
								strcat(object_code, operand_address);
							}
							else{
								printf("[ERROR] Invalid operand\n");
								printf("[ERROR LINE] %s", curr->full_line);
								return 1;
							}
						}

						/* Format 3, immediate addressing */
						else if(curr->format == 3){
							if(curr->addressing_mode == 1){
								if(curr->index == 1){
									strcat(object_code, "8");
								}
								else{
									strcat(object_code, "0");
								}
								int over_dec=0;
								for(unsigned int i=0;i<strlen(curr->operand);i++){ // 10진수
									if((curr->operand[i]<'0')||(curr->operand[i]>'9')){
										over_dec=1;
									}
								}
								if(over_dec == 0){
									int temp = strtol(curr->operand, NULL, 10);
									sprintf(operand_address, "%03X", temp);
									strcat(object_code, operand_address);
								}
								else{
									printf("[ERROR] Invalid operand\n");
									printf("[ERROR LINE] %s", curr->full_line);
									return 1;
								}
							}
							else{
								printf("[ERROR] Invalid operand\n");
								printf("[ERROR LINE] %s", curr->full_line);
								return 1;
							}
						}
					}
				}else{
					/* if operand == NULL, RSUB같은 경우 */
					if(strcmp(curr->instruction, "RSUB")==0){
						strcat(object_code, "0000");
					}
					else{
						if(curr->format != 1){
							printf("[ERROR] No operand\n");
							printf("[ERROR LINE] %s", curr->full_line);
							return 1;
						}
					}
				}
			}
			/* Assembler directives */
			else if((strcmp(curr->instruction, "BYTE")==0)||(strcmp(curr->instruction, "WORD")==0)){
				char ascii[30]="\0";
				if(curr->operand[0]=='C'){
					//character
					for(unsigned int i=2;i<strlen(curr->operand)-1;i++){
						sprintf(ascii, "%X", curr->operand[i]);
						strcat(object_code, ascii);
					}
				}
				else if(curr->operand[0]=='X'){
					//hexadecimal
					for(unsigned int i=2;i<strlen(curr->operand)-1;i++){ // 16진수
						if(curr->operand[i] >= '0' && curr->operand[i] <= '9'){
						}else if(curr->operand[i] >= 'A' && curr->operand[i] <= 'F'){
						}else if(curr->operand[i] >= 'a' && curr->operand[i] <= 'f'){
						}else{
							/* Impossible to convert */
							printf("[ERROR] Invalid operand\n");
							printf("[ERROR LINE] %s", curr->full_line);
							return 1;
						}
						sprintf(ascii, "%c", curr->operand[i]);
						strcat(object_code, ascii);
					}
				}
				else{
					printf("[ERROR] Wrong format\n");
					printf("[ERROR LINE] %s", curr->full_line);
					return 1;
				}
			}
			else if(strcmp(curr->instruction, "BASE")==0){
				int base_address = search_operand(curr->operand);
				if(base_address >= 0){
					BASE = base_address;
				}
			}
			
		}
		strcpy(curr->obj_code, object_code);
		strcpy(object_code, "\0");
		curr=curr->next;
	}
	if(strcmp(curr->instruction, "END")==0){
		strcpy(curr->obj_code, "\0");
	}
	return 0;
}





/* Assemble이 성공적으로 완료되면 lst, obj 파일 작성 */
int assemble(char *filename){
	int result1=0;
	int result2=0;
	symbol_success=0;
	char text_record[70]="\0";
	int text_record_length=0;
	int text_record_starting_address=0;
	char modify_record[COMMAND_MAX_LEN]="\0";
	int total_byte=0;
	result1 = assemble_pass1(filename);
	if(result1 == 0){
		/* Assemble pass1 SUCCESS */
		result2 = assemble_pass2();
		if(result2 == 0){
			/* Assemble pass2 SUCCESS */
			//filename = strtok(filename, ".asm");
			filename[strlen(filename)-4]='\0';
			char lst_filename[30]="\0";
			char obj_filename[30]="\0";
			strcat(lst_filename, filename);
			strcat(lst_filename, ".lst");
			strcat(obj_filename, filename);
			strcat(obj_filename, ".obj");

			FILE *lst_fp = fopen(lst_filename, "w");
			FILE *obj_fp = fopen(obj_filename, "w");

			struct asm_line* curr = asm_head->next;
			struct asm_line* prev = curr;
			while (curr != NULL) {
				/* listing file */
				if(strcmp(curr->instruction, "COMMENT")!=0&&strcmp(curr->instruction, "BLANK")!=0){
					fprintf(lst_fp, "%d\t", curr->line_num);
					if(curr->address >= 0) fprintf(lst_fp, "%04X\t", curr->address);
					else fprintf(lst_fp, "\t");
					if(curr->full_line != NULL){
						curr->full_line[strlen(curr->full_line)-1]='\0';
						fprintf(lst_fp, "%-30s\t", curr->full_line);
					}else fprintf(lst_fp, "\t");
		
					if(curr->obj_code != NULL) fprintf(lst_fp, "%s\t", curr->obj_code);
					else fprintf(lst_fp, "\t");
					fprintf(lst_fp, "\n");
				}
				else if(strcmp(curr->instruction, "COMMENT")==0){
					fprintf(lst_fp, "%d\t", curr->line_num);
					fprintf(lst_fp, "%s", curr->full_line);
				}


				/* object file */
				if(strcmp(curr->instruction, "START")==0){
					fprintf(obj_fp, "H");
					fprintf(obj_fp, "%-6s", curr->label);
					fprintf(obj_fp, "%06X", starting_address);
					fprintf(obj_fp, "%06X\n", program_length);
				}
				else if(strcmp(curr->instruction, "END")!=0){
					if(curr->obj_code != NULL){
						if(text_record_length == 0){
							text_record_starting_address = curr->address;
						}
						text_record_length += strlen(curr->obj_code);
						total_byte += (strlen(curr->obj_code)/2);
						if(text_record_length <= 60){
							/* text record에 아직 쓸수있음 */
							strcat(text_record, curr->obj_code);
						}
						else{
							/* text record 꽉 차서 못씀, 파일에 쓰고 다음줄로 */
							text_record_length -= strlen(curr->obj_code);
							fprintf(obj_fp, "T");
							fprintf(obj_fp, "%06X", text_record_starting_address);
							fprintf(obj_fp, "%02X", text_record_length/2);
							fprintf(obj_fp, "%s\n", text_record);
							text_record_length = strlen(curr->obj_code);
							text_record_starting_address = curr->address;
							strcpy(text_record, "\0");
							strcat(text_record, curr->obj_code);
						}
						if((strcmp(curr->instruction, "RESW")==0)||(strcmp(curr->instruction, "RESB")==0)){
							/* RESW, RESB인 경우는 빈칸 & 줄바꿈 */
							if(text_record_length > 0){
								fprintf(obj_fp, "T");
								fprintf(obj_fp, "%06X", text_record_starting_address);
								fprintf(obj_fp, "%02X", text_record_length/2);
								fprintf(obj_fp, "%s\n", text_record);
								text_record_length = 0;
								text_record_starting_address = 0;
								strcpy(text_record, "\0");		
							}
						}
					}
					if((curr->format == 4)&&(curr->addressing_mode != IMMEDIATE)){
						/* Modification record, direct addressing */
						strcat(modify_record, "M");
						char temp_record[10]="\0";
						sprintf(temp_record, "%06X", (total_byte-3));
						strcat(modify_record, temp_record);
						strcat(modify_record, "05\n");
					}
				}
				else if(strcmp(curr->instruction, "END")==0){
					if(text_record != NULL){
						fprintf(obj_fp, "T");
						fprintf(obj_fp, "%06X", text_record_starting_address);
						fprintf(obj_fp, "%02X", text_record_length/2);
						fprintf(obj_fp, "%s\n", text_record);
					}
					if(modify_record != NULL){
						fprintf(obj_fp, "%s", modify_record);
					}
					fprintf(obj_fp, "E");
					fprintf(obj_fp, "%06X\n", starting_address);
				}


				prev = curr;
				curr = curr->next;
				free(prev);
			}
			fclose(lst_fp);
			fclose(obj_fp);
	
			asm_head->next = NULL;
	
			symbol_success=1;
			symbol();
			printf("[%s], [%s]\n", lst_filename, obj_filename);
			return 0;
		}
		else{
			/* Pass2 도중에 실패한 경우 */
			printf("[ERROR] Assemble Fail during Pass2\n");
			struct asm_line* curr = asm_head->next;
			struct asm_line* prev = curr;
			while (curr != NULL) {
				prev = curr;
				curr = curr->next;
				free(prev);
			}
			asm_head->next = NULL;

			struct symbol* s_curr = symbol_table_head->next;
			struct symbol* s_prev = s_curr;
			while(s_curr != NULL){
				s_prev = s_curr;
				s_curr=s_curr->next;
				free(s_prev);
			}
			symbol_table_head->next = NULL;
		}
	}
	else{
		/* Pass1 도중에 실패한 경우 */
		printf("[ERROR] Assemble Fail during Pass1\n");
		struct asm_line* curr = asm_head->next;
		struct asm_line* prev = curr;
		while (curr != NULL) {
			prev = curr;
			curr = curr->next;
			free(prev);
		}
		asm_head->next = NULL;

		struct symbol* s_curr = symbol_table_head->next;
		struct symbol* s_prev = s_curr;
		while(s_curr != NULL){
			s_prev = s_curr;
			s_curr=s_curr->next;
			free(s_prev);
		}
		symbol_table_head->next = NULL;
	}
	return 1;
}





/* 성공적으로 assemble된 asm 파일에 대한 symbol table 만들기 */
void symbol(){
	if(symbol_success == 1){
		int i=0;
		struct symbol* s_curr = symbol_table_head->next;
		struct symbol* s_prev = s_curr;
		while(s_curr != NULL){
			ordered_symbol[i].name = malloc(sizeof(s_curr->name));
			strcpy(ordered_symbol[i].name, s_curr->name);
			ordered_symbol[i].address = s_curr->address;
			s_prev = s_curr;
			s_curr=s_curr->next;
			free(s_prev);
			i++;
		}
		symbol_table_head->next = NULL;

		/* Bubble Sort */
		struct symbol temp;
		for(int j=0;j<i;j++){
			for(int k=0;k<i-1;k++){
				if(strcmp(ordered_symbol[k].name ,ordered_symbol[k+1].name)>0){
					temp = ordered_symbol[k];
					ordered_symbol[k] = ordered_symbol[k+1];
					ordered_symbol[k+1] = temp;
				}
			}
		}
		symbol_count = i;
	}
}





/* Symbol table 출력하기 */
void symbol_print(){
	for(int l=0;l<symbol_count;l++){
		printf("\t%s\t%04X\n", ordered_symbol[l].name, ordered_symbol[l].address);
	}
	if(symbol_count == 0){
		printf("There is no symbol table\n");
	}
}
