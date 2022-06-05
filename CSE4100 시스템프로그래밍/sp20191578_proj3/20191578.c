#include "20191578.h"

int main(void){

	struct command command;

	/* Allocate & Initialize memory - history LinkedList */
	head = malloc(sizeof(struct history_node));
	head->next = NULL;
	head->command = NULL;

	/* Allocate & Initialize memory - memory */
	memory = malloc(MEMORY_MAX_SIZE);
	memset(memory,0,MEMORY_MAX_SIZE);

	/* Initialize global variable */
	stored_start = 0;
	progaddr = 0;
	csaddr = -1;
	symtab_index = 0;
	breakpoint_num = 0;
	for(int i=0;i<100;i++){
		breakpoint[i]=0;
	}
	regA=0, regX=0, regL=0, regPC=0, regB=0, regS=0, regT=0, condition_code=0;

	/* Allocate & Initialize memory - opcode linkedlist */
	for(int i=0;i<OPCODE_HASH_TABLE_SIZE;i++){
		opcode_head[i] = malloc(sizeof(struct opcode_hash_table_node));
		opcode_head[i]->opcode = i;
		opcode_head[i]->instruction = NULL;
		opcode_head[i]->format = NULL;
		opcode_head[i]->next = NULL;
	}
	

	/* Read "opcode.txt" file and make Opcode hash table */
	FILE *fp = fopen("opcode.txt", "r");
	int val=0;
	char name[COMMAND_MAX_LEN];
	char form[COMMAND_MAX_LEN];
	int hash_index=0;
	while(fscanf(fp, "%X %s %s", &val, name, form) != EOF){
		struct opcode_hash_table_node *newnode = malloc(sizeof(struct opcode_hash_table_node));
		newnode->opcode = val;
		newnode->instruction = malloc(sizeof(COMMAND_MAX_LEN));
		strcpy(newnode->instruction, name);
		newnode->format = malloc(sizeof(COMMAND_MAX_LEN));
		strcpy(newnode->format, form);

		/* Distribute evenly from 0 to 19 */
		hash_index = (val%21)%20;
		newnode->next = opcode_head[hash_index]->next;
		opcode_head[hash_index]->next = newnode;
	}

	fclose(fp);

	asm_head = malloc(sizeof(struct asm_line));
	asm_head->next = NULL;
	symbol_table_head = malloc(sizeof(struct symbol));
	symbol_table_head->next = NULL;
	

	while(1){
		/* Shell input prompt */
		char *cmd;
		cmd = malloc(COMMAND_MAX_LEN*sizeof(char));
		strcpy(cmd, "0");

		printf("sicsim> ");
		scanf("%[^\n]s", cmd);
		getchar();

		/* Divide input sentence into valid piece */
		char *cmd2;
		cmd2 = malloc(strlen(cmd)*sizeof(char));
		strcpy(cmd2, cmd);
	
		command.input_full = cmd;
		command.input_num = 0;
		command.error_type = 0;
		command.input_piece[command.input_num] = strtok(cmd2, " ,\t\n");
		while(command.input_piece[command.input_num] != NULL){
			command.input_piece[++(command.input_num)] = strtok(NULL, " ,\t\n");
		}

		/* If there is no input */
		if(command.input_piece[0] == NULL) {
			printf("[ERROR] INVALID INPUT!\n");
			continue;
		}

		/* Functions according to each Command */

		/* help */
		if((strcmp(command.input_piece[0], "help")==0)||(strcmp(command.input_piece[0], "h")==0)){
			/* Invalid input form */
			if(command.input_num > 1){
				command.error_type = 2;
			}

			/* Valid input form(no error) */
			if(command.error_type == 0){
				help();
				add_history(command.input_piece[0]);
			}
		}


		/* dir */
		else if((strcmp(command.input_piece[0], "dir")==0)||(strcmp(command.input_piece[0], "d")==0)){
			/* Invalid input form */
			if(command.input_num > 1){
				command.error_type = 2;
			}

			/* Valid input form(no error) */
			if(command.error_type == 0){
				dir();
				add_history(command.input_piece[0]);
			}
		}


		/* quit */
		else if((strcmp(command.input_piece[0], "quit")==0)||(strcmp(command.input_piece[0], "q")==0)){
			/* Invalid input form */
			if(command.input_num > 1){
				command.error_type = 2;
			}

			/* Valid input form(no error) */
			if(command.error_type == 0){
				quit();
				break;
			}
		}


		/* history */
		else if((strcmp(command.input_piece[0], "history")==0)||(strcmp(command.input_piece[0], "hi")==0)){
			/* Invalid input form */
			if(command.input_num > 1){
				command.error_type = 2;
			}

			/* Valid input form(no error) */
			if(command.error_type == 0){
				add_history(command.input_piece[0]);
				print_history();
			}
		}


		/* dump */
		else if((strcmp(command.input_piece[0], "dump")==0)||(strcmp(command.input_piece[0], "du")==0)){
			/* Invalid input form */
			if(command.input_num > 3){
				command.error_type = 2;
			}else if(command.input_num == 3){
				/* Valid input form(no error) - case of 'dump start, end' 
				   There must be 1 comma */
				char *result;
				result = strstr(command.input_full, command.input_piece[1]);
				result = strstr(result, ",");
				/* Arguments are not separated by comma */
				if(result == NULL){
					command.error_type = 2;
				}
			}

			/* Valid input form(no error) */
			if(command.error_type == 0){
				int start=0;
				int end=0;

				/* Store refined command */
				char *final_command;
				final_command = malloc(COMMAND_MAX_LEN);
				strcpy(final_command, command.input_piece[0]);

				/* Calculate start address and end address */
				if(command.input_num == 1){
					/* dump */
					start = stored_start;
					end = start + 159;
					if(end > 1048575) end = MEMORY_MAX_SIZE-1;
				}else if(command.input_num == 2){
					/* dump start */
					start = check_valid_input_16(command.input_piece[1]);
					end = start + 159;
					if(end > 1048575) end = MEMORY_MAX_SIZE-1;
					strcat(final_command, " ");
					strcat(final_command, command.input_piece[1]);
				}else if(command.input_num == 3){
					/* dump start, end */
					start = check_valid_input_16(command.input_piece[1]);
					end = check_valid_input_16(command.input_piece[2]);
					if(end > 1048575) end = -1;
					strcat(final_command, " ");
					strcat(final_command, command.input_piece[1]);
					strcat(final_command, ", ");
					strcat(final_command, command.input_piece[2]);
				}

				if(start > 1048575) start = -1;
				if((start != -1)&&(end != -1)&&(start > end)) start = -1;

				/* All arguments can be converted to hexadecimal properly */
				if((start!=-1)&&(end!=-1)) {
					dump(&start, &end);
					add_history(final_command);
				}else{
					command.error_type = 2;
				}
			}
		}


		/* edit */
		else if((strcmp(command.input_piece[0], "edit")==0)||(strcmp(command.input_piece[0], "e")==0)){
			/* Invalid input form */
			if(command.input_num != 3){
				command.error_type = 2;
			}else if(command.input_num == 3){
				/* Valid input form(no error) - case of 'edit address, value' 
				   There must be 1 comma */
				char *result;
				result = strstr(command.input_full, command.input_piece[1]);
				result = strstr(result, ",");
				/* Arguments are not separated by comma */
				if(result == NULL){
					command.error_type = 2;
				}
			}
			/* Valid input form(no error) */
			if(command.error_type == 0){
				int address=0;
				int value=0;

				/* Store refined command */
				char *final_command;
				final_command = malloc(COMMAND_MAX_LEN);
				strcpy(final_command, command.input_piece[0]);
				strcat(final_command, " ");
				strcat(final_command, command.input_piece[1]);
				strcat(final_command, ", ");
				strcat(final_command, command.input_piece[2]);

				/* Convert address and value into integer */
				address = check_valid_input_16(command.input_piece[1]);
				value = check_valid_input_16(command.input_piece[2]);
				if(address > 1048575) address = -1;
				if(value < 0 || value > 255) value = -1;

				/* All arguments can be converted to hexadecimal properly */
				if((address!=-1)&&(value!=-1)){
					edit(address, value);
					add_history(final_command);
				}else{
					command.error_type = 2;
				}
			}
		}


		/* fill */
		else if((strcmp(command.input_piece[0], "fill")==0)||(strcmp(command.input_piece[0], "f")==0)){
			/* Invalid input form */
			if(command.input_num != 4){
				command.error_type = 2;
			}else if(command.input_num == 4){
				/* Valid input form(no error) - case of 'fill start, end, value' 
				   There must be 2 comma */
				char *result;
				result = strstr(command.input_full, command.input_piece[1]);
				result = strstr(result, ",");

				/* Arguments are not separated by comma */
				if(result == NULL){
					command.error_type = 2;
				}else{
					result = strstr(result+1, ",");
					if(result == NULL){
						command.error_type = 2;
					}
				}
			}
			/* Valid input form(no error) */
			if(command.error_type == 0){
				int start=0;
				int end=0;
				int value=0;

				/* Store refined command */
				char *final_command;
				final_command = malloc(COMMAND_MAX_LEN);
				strcpy(final_command, command.input_piece[0]);
				strcat(final_command, " ");
				strcat(final_command, command.input_piece[1]);
				strcat(final_command, ", ");
				strcat(final_command, command.input_piece[2]);
				strcat(final_command, ", ");
				strcat(final_command, command.input_piece[3]);

				/* Calculate and Convert start address, end address, and value into integer */
				start = check_valid_input_16(command.input_piece[1]);
				end = check_valid_input_16(command.input_piece[2]);
				value = check_valid_input_16(command.input_piece[3]);
				if(start > 1048575) start = -1;
				if(end > 1048575) end = -1;
				if(value < 0 || value > 255) value = -1;

				/* All arguments can be converted to hexadecimal properly */
				if((start!=-1)&&(end!=-1)&&(value!=-1)&&(end >= start)){
					fill(start, end, value);
					add_history(final_command);
				}else{
					command.error_type = 2;
				}
			}
		}


		/* reset */
		else if(strcmp(command.input_piece[0], "reset")==0){
			/* Invalid input form */
			if(command.input_num > 1){
				command.error_type = 2;
			}
			/* Valid input form(no error) */
			if(command.error_type == 0){
				reset();
				add_history(command.input_piece[0]);
			}
		}


		/* opocde mnemonic */
		else if(strcmp(command.input_piece[0], "opcode")==0){
			/* Invalid input form */
			if(command.input_num != 2){
				command.error_type = 2;
			}
			/* Valid input form(no error) */
			if(command.error_type == 0){
				int match = 0;
				match = opocde_mnemonic(command.input_piece[1]);
				/* There is a corresponding mnemonic in opcodelist */
				if(match == 0){
					/* Store refined command */
					char *final_command;
					final_command = malloc(COMMAND_MAX_LEN);
					strcpy(final_command, command.input_piece[0]);
					strcat(final_command, " ");
					strcat(final_command, command.input_piece[1]);
					add_history(final_command);
				}else{
					command.error_type = 2;
				}
			}
		}


		/* opocdelist */
		else if(strcmp(command.input_piece[0], "opcodelist")==0){
			/* Invalid input form */
			if(command.input_num > 1){
				command.error_type = 2;
			}
			/* Valid input form(no error) */
			if(command.error_type == 0){
				opcodelist();
				add_history(command.input_piece[0]);
			}
		}

		/* type */
		else if(strcmp(command.input_piece[0], "type") == 0){
			if(command.input_num != 2){
				command.error_type = 2;
			}

			if(command.error_type == 0){
				if(type(command.input_piece[1])==0){
					char *final_command;
					final_command = malloc(COMMAND_MAX_LEN);
					strcpy(final_command, command.input_piece[0]);
					strcat(final_command, " ");
					strcat(final_command, command.input_piece[1]);
					add_history(final_command);
				}
			}
		}

		/* assemble */
		else if(strcmp(command.input_piece[0], "assemble") == 0){
			if(command.input_num != 2){
				command.error_type = 2;
			}
			if(command.error_type == 0){
				char* ptr = strstr(command.input_piece[1], ".asm");
				if (ptr == NULL) {
					command.error_type = 2;
				}
				else{
					if(assemble(command.input_piece[1])==0){
						char *final_command;
						final_command = malloc(COMMAND_MAX_LEN);
						strcpy(final_command, command.input_piece[0]);
						strcat(final_command, " ");
						strcat(final_command, command.input_piece[1]);
						strcat(final_command, ".asm");
						add_history(final_command);
					}
				}
			}
		}

		/* symbol */
		else if(strcmp(command.input_piece[0], "symbol") == 0){
			if(command.input_num > 1){
				command.error_type = 2;
			}
			if(command.error_type == 0){
				symbol_print();
				add_history(command.input_piece[0]);
			}
		}

		/* program address setting */
		else if(strcmp(command.input_piece[0], "progaddr") == 0){
			if(command.input_num != 2){
				command.error_type = 2;
			}
			if(command.error_type == 0){
				if(progaddr_set(command.input_piece[1]) == 0){
					char *final_command;
					final_command = malloc(COMMAND_MAX_LEN);
					strcpy(final_command, command.input_piece[0]);
					strcat(final_command, " ");
					strcat(final_command, command.input_piece[1]);
					add_history(final_command);
				}
			}
		}

		/* linking loader */
		else if(strcmp(command.input_piece[0], "loader") == 0){
			if(command.input_num > 4||command.input_num == 1){
				command.error_type = 2;
			}
			if(command.error_type == 0){
				if(loader(command.input_piece[1], command.input_piece[2], command.input_piece[3], command.input_num-1) == 0){
					regA=0, regX=0, regB=0, regS=0, regT=0;
					add_history(command.input_full);
				}
				else{
					command.error_type = 2;
				}
			}
		}

		/* breakpoint */
		else if(strcmp(command.input_piece[0], "bp")==0){
			if(command.input_num > 2){
				command.error_type = 2;
			}
			if(command.error_type == 0){
				if(command.input_num == 1){
					//print every breakpoint
					printf("\t\tbreakpoint\n");
					printf("\t\t----------\n");
					for(int i=0;i<breakpoint_num;i++){
						printf("\t\t%X\n", breakpoint[i]);
					}
					if(breakpoint_num == 0){
						printf("\t\tNo breakpoint\n");
					}
				}
				else{
					if(strcmp(command.input_piece[1], "clear") == 0){
						//clear all breakpoint
						for(int i=0;i<breakpoint_num;i++){
							breakpoint[i]=0;
						}
						breakpoint_num = 0;
						printf("\t\t[ok] clear all breakpoints\n");
					}
					else{
						//create breakpoint
						create_breakpoint(command.input_piece[1]);
					}
				}
				add_history(command.input_full);
			}
		}

		/* run */
		else if(strcmp(command.input_piece[0], "run")==0){
			if(command.input_num > 1){
				command.error_type = 2;
			}
			if(command.error_type == 0){
				run();
				add_history(command.input_full);
			}
		}

		/* Invalid input */
		else{
			command.error_type = 1;
		}
		
		/* Invalid input error */
		if(command.error_type==1){
			printf("[ERROR] INVALID INPUT!\n");
		}
		/* Argument error */
		else if(command.error_type==2){
			printf("[ERROR] WRONG ARGUMENT!\n");
		}
	}

	return 0;
}





/*
===============================
command: h[elp]
function: Show a list of inputable commands.
arguments: none
return value: none
===============================
 */
void help(){
	printf("h[elp]\n");
	printf("d[ir]\n");
	printf("q[uit]\n");
	printf("hi[story]\n");
	printf("du[mp] [start, end]\n");
	printf("e[dit] address, value\n");
	printf("f[ill] start, end, value\n");
	printf("reset\n");
	printf("opcode mnemonic\n");
	printf("opcodelist\n");
	printf("assemble filename\n");
	printf("type filename\n");
	printf("symbol\n");
}





/*
===============================
command: d[ir]
function: Show the files in the current directory.
arguments: none
return value: none
===============================
 */
void dir(){
	struct dirent *de = NULL;
	struct stat stat;
	DIR *dr = opendir(".");
	if(dr == NULL){
		printf("Cannot open current directory.\n");
		return;
	}
	while((de = readdir(dr)) != NULL){
		if(de->d_type == DT_REG){
			lstat(de->d_name, &stat);
			if(S_IXUSR & stat.st_mode){
				/* 실행파일 */
				printf("\t%s*\n", de->d_name);
			}else{
				/* Normal file */
				printf("\t%s\n", de->d_name);
			}
		}
		else if(de->d_type == DT_DIR){
			/* Directory */
			printf("\t%s/\n", de->d_name);
		}
		else{
			/* Directory */
			printf("\t%s/\n", de->d_name);
		}
	}
	closedir(dr);
}





/*
===============================
command: none
function: Add newnode to history linkedlist.
arguments: char *cmd - refined command
return value: none
===============================
 */
void add_history(char *cmd){
	int i=1;
	/* Find the last node in history linkedlist */
	struct history_node *curr = head;
	while(curr->next != NULL){
		curr=curr->next;
		i++;
	}
	/* Add newnode to the end of history linkedlist */
	struct history_node *newnode = malloc(sizeof(struct history_node));
	newnode->command = cmd;
	newnode->order = i;
	newnode->next = curr->next;
	curr->next = newnode;
}





/*
===============================
command: hi[story]
function: Print all nodes in history linkedlist.
arguments: none
return value: none
===============================
 */
void print_history(){
	struct history_node *curr = head->next;
	while(curr != NULL){
		printf("\t%d \t%s\n", curr->order, curr->command);
		curr=curr->next;
	}
}





/*
===============================
command: du[mp] [start, end]
function: Print the memory contents from start to end.
arguments: int *start - start address
		   int *end   - end address
return value: none
===============================
 */
void dump(int *start, int *end){
	int address_start = 0;
	int address_end = 0;
	address_start = *start/16 * 16;
	address_end = (*end+16)/16 * 16;
	for(int base = address_start; base < address_end; base+=16){
		/* Left(address) */
		printf("%05X ", base);

		/* Middle(hexadecimal) */
		for(int i=0;i<16;i++){
			if(base+i < *start || base+i > *end){
				printf("   ");
			}
			else
				printf("%02X ", ((uint8_t*)memory)[base+i]);
			if( i%16 == 15 ) printf("; ");
		}

		/* Right(ascii code) */
		for(int i=0;i<16;i++){
			if(base+i < *start || base+i > *end){
				printf(".");
			}
			else if(((uint8_t*)memory)[base+i]>=0x20 && ((uint8_t*)memory)[base+i]<=0x7E){
				printf("%c", (char)((uint8_t*)memory)[base+i]);
			}else{
				printf(".");
			}
			if( i%16 == 15 ) printf("\n");
		}
	}

	/* Update next start point */
	stored_start = *end + 1;
	if(stored_start >= MEMORY_MAX_SIZE){
		stored_start = 0;
	}
}





/*
===============================
command: none
function: Check whether it can be converted to hexadecimal.
arguments: char *num_str - String to convert to hexadecimal
return value: result  - convert success
			  -1 	  - convert fail
===============================
 */
int check_valid_input_16(char *num_str){
	/* Check the range */
	for(unsigned int i=0;i<strlen(num_str);i++){
		if(num_str[i] >= '0' && num_str[i] <= '9'){
		}else if(num_str[i] >= 'A' && num_str[i] <= 'F'){
		}else if(num_str[i] >= 'a' && num_str[i] <= 'f'){
		}else{
			/* Impossible to convert */
			return -1;
		}
	}
	int result;
	result = strtol(num_str, NULL, 16);
	return result;
}





/*
===============================
command: e[dit] address, value 
function: Changes the value of a specific address in memory.
arguments: int address - address to be replaced
		   int value   - value to be replaced
return value: none
===============================
 */
void edit(int address, int value){
	((uint8_t*)memory)[address] = value;
}





/*
===============================
command: f[ill] start, end, value
function: Changes the value of a particular interval in memory.
arguments: int start - start address of interval to be replaced
		   int end   - end address of interval to be replaced
		   int value - value to be replaced
return value: none
===============================
 */
void fill(int start, int end, int value){
	for(int i=start;i<=end;i++){
		((uint8_t*)memory)[i] = value;
	}
}





/*
===============================
command: reset 
function: Initialize the memory to zero.
arguments: none
return value: none
===============================
 */
void reset(){
	memset(memory,0,MEMORY_MAX_SIZE);
}





/*
===============================
command: opcode mnemonic 
function: Search and show the opcode corresponding to mnemonic.
arguments: char *mnemonic - mnemonic to search
return value: 0 - search success
			 -1 - search fail
===============================
 */
int opocde_mnemonic(char *mnemonic){
	for(int i=0;i<OPCODE_HASH_TABLE_SIZE;i++){
		struct opcode_hash_table_node *curr = opcode_head[i]->next;
		while(curr != NULL){
			if(strcmp(mnemonic, curr->instruction) == 0){
				printf("opocde is %02X\n", curr->opcode);
				return 0;
			}
			curr = curr->next;
		}
	}
	printf("[ERROR] No opcode matches input.\n");
	return -1;
}





/*
===============================
command: opcodelist 
function: Print out all the contents of the opcodelist. 
arguments: none
return value: none
===============================
 */
void opcodelist(){
	for(int i=0;i<OPCODE_HASH_TABLE_SIZE;i++){
		printf("%d : ", i);
		struct opcode_hash_table_node *curr = opcode_head[i]->next;
		while(curr != NULL){
			if(curr->next != NULL) printf("[%s, %02X] -> ", curr->instruction, curr->opcode);
			else printf("[%s, %02X]\n", curr->instruction, curr->opcode);
			curr = curr->next;
		}
	}
}





/*
===============================
command: q[uit] 
function: Exit the program.
arguments: none
return value: none
===============================
 */
void quit(){
	/* history linkedlist free */
	struct history_node *curr = head->next;
	struct history_node *prev = head->next;
	while(curr != NULL){
		//printf("curr: %p\n", &curr);
		//printf("curr->name: %p(%s)\n", &(curr->command), curr->command);
		prev = curr;
		//free(prev);
		curr = curr->next;
		free(prev);
	}
	free(head);

	/* memory free */
	free(memory);

	/* opcode linkedlist free */
	for(int i=0;i<OPCODE_HASH_TABLE_SIZE;i++){
		struct opcode_hash_table_node *curr = opcode_head[i]->next;
		struct opcode_hash_table_node *prev = opcode_head[i]->next;
		while(curr != NULL){
			prev = curr;
			free(prev);
			curr = curr->next;
		}
		free(opcode_head[i]);
	}
}





/* program starting address setting */
int progaddr_set(char* address){
	progaddr = strtol(address, NULL, 16);
	regPC = progaddr;
	return 0;
}





/* linking loader */
int loader(char* filename1, char* filename2, char* filename3, int file_num){
//	printf("파일은 %d개\n", file_num);
//	printf("filename1: %s\n", filename1);
//	printf("filename2: %s\n", filename2);
//	printf("filename3: %s\n", filename3);

	int error_flag = 0;
	if(file_num == 1){
		//filename1
		if(loader_pass1(filename1) == 0){
			if(loader_pass2(filename1) == 0){
				//printf("pass1 success\n");
				//printf("pass2 success\n");
			} else error_flag = 1;
		} else error_flag = 1;
	}

	else if(file_num == 2){
		//filename2
		if(loader_pass1(filename1) == 0){
			if(loader_pass1(filename2) == 0){
				//printf("pass1 success\n");
			} else error_flag = 1;
		}else error_flag = 1;

		if(error_flag == 0){
			if(loader_pass2(filename1) == 0){
				if(loader_pass2(filename2) == 0){
					//printf("pass2 success\n");
				} else error_flag = 1;
			}else error_flag = 1;	
		}
	}

	else if(file_num == 3){
		//filename3
		if(loader_pass1(filename1) == 0){
			if(loader_pass1(filename2) == 0){
				if(loader_pass1(filename3) == 0){
					//printf("pass1 success\n");
				} else error_flag = 1;
			} else error_flag = 1;
		}else error_flag = 1;

		if(error_flag == 0){
			if(loader_pass2(filename1) == 0){
				if(loader_pass2(filename2) == 0){
					if(loader_pass2(filename3) == 0){
						//printf("pass2 success\n");
					} else error_flag = 1;
				} else error_flag = 1;
			}else error_flag = 1;	
		}
	}

	if(error_flag == 0){
		print_symtab();
		for(int i=0;i<symtab_index;i++){
			for(unsigned int j=0;j<strlen(symtab[i].control_section);j++){
				symtab[i].control_section[j] = '\0';
			}
			for(unsigned int j=0;j<strlen(symtab[i].symbol_name);j++){
				symtab[i].symbol_name[j] = '\0';
			}
			symtab[i].address = 0;
			symtab[i].length = 0;
		}
		progaddr = 0;
		csaddr = -1;
		symtab_index = 0;
	}
	else{
		printf("[ERROR] load Fail\n");
		error_flag = 0;
	}

	return 0;
}





/* loader pass 1 */
int loader_pass1(char* filename){
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		printf("[ERROR] No file!\n");
		return 1;
	}

	if(csaddr == -1){
		/* first control section */
		csaddr = progaddr;
	}

	char line[COMMAND_MAX_LEN]="\0";
	char temp[100];
	int temp_int=0;
	int curr_csaddr=0;
	while(!feof(fp)){
		if(fgets(line, COMMAND_MAX_LEN, fp)==NULL) break;
		if(line[0]=='H'){
			//printf("Header\t");
			//char temp[100];
			//int temp_int=0;
			strncpy(temp, line+1, 6);
			if(search_symtab(temp) != -1){
				printf("[ERROR]Duplicate external symbol");
				return 1;
			}
			strcpy(symtab[symtab_index].control_section, temp);
			strcpy(symtab[symtab_index].symbol_name, "\0");
			strcpy(temp, "\0");

			strncpy(temp, line+7, 6);
			temp_int = strtol(temp, NULL, 16);
			symtab[symtab_index].address = csaddr + temp_int;
			curr_csaddr = csaddr + temp_int;
			strcpy(temp, "\0");

			strncpy(temp, line+13, 6);
			temp_int = strtol(temp, NULL, 16);
			symtab[symtab_index].length = temp_int;
			strcpy(temp, "\0");

			csaddr = csaddr + temp_int;
			symtab_index++;
		}
		else if(line[0]=='D'){
			//printf("Define\t");
			unsigned int d_num = (strlen(line)-2)/12;
			for(unsigned int i=0;i<d_num;i++){
				strncpy(temp, line+(12*i)+1, 6);
				if(search_symtab(temp) != -1){
					printf("[ERROR]Duplicate external symbol");
					return 1;
				}
			
				strcpy(symtab[symtab_index].symbol_name, temp);
				strcpy(symtab[symtab_index].control_section, "\0");
				strcpy(temp, "\0");

				strncpy(temp, line+(12*i)+7, 6);
				temp_int = strtol(temp, NULL, 16);
				//printf("address: %04X\n", temp_int);
				//printf("csaddr: %04X\n", csaddr);
				symtab[symtab_index].address = curr_csaddr + temp_int;
				strcpy(temp, "\0");

				symtab_index++;
			}
		//printf("%s(%d)", line, strlen(line));
		}
		//printf("%s(%d)", line, strlen(line));
	}

	fclose(fp);
	return 0;
}





/* loader pass 2 */
int loader_pass2(char* filename){
	//printf("pass2 %s\n", filename);
	int ref_array[100];

	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		printf("[ERROR] No file!\n");
		return 1;
	}

	char line[COMMAND_MAX_LEN]="\0";
	char temp[100];
	int temp_int=0;
	int external_address=0;
	while(!feof(fp)){
		if(fgets(line, COMMAND_MAX_LEN, fp)==NULL) break;
		if(line[0] == 'H'){
			strncpy(temp, line+1, 6);
			csaddr = search_symtab(temp);
			if(csaddr == -1){
				printf("[ERROR]No external symbol\n");
				return 1;
			}
			ref_array[1] = csaddr;
			//printf("starting address of control section '%s' is %04X\n", temp, csaddr);
		}
		else if(line[0] == 'R'){
			unsigned int r_num = (strlen(line)-2)/8;
			if(8*r_num+1 < strlen(line)){
				r_num++;
			}
			for(unsigned int i=0;i<r_num;i++){
				strncpy(temp, line+(8*i)+1, 2);
				temp_int = strtol(temp, NULL, 10);
				strcpy(temp, "\0");

				if(i == r_num-1){
					strcpy(temp, line+(8*i)+3);
					//printf("temp(%d)\n", strlen(temp));
					for(unsigned int i=strlen(temp)-1;i<6;i++){
						temp[i] = ' ';
					}
					temp[6] = '\0';
				} else	strncpy(temp, line+(8*i)+3, 6);

				external_address = search_symtab(temp);
				//printf("%s's external address: %04X\n", temp, external_address);
				if(external_address == -1){
					printf("[ERROR]No external symbol\n");
					return 1;
				}
				else{
					ref_array[temp_int] = external_address;
				}
				strcpy(temp, "\0");
			}
		}
		else if(line[0] == 'T'){
			int curr_csaddr = csaddr;
			int length = 0;
			strncpy(temp, line+1, 6);
			temp_int = strtol(temp, NULL, 16); //starting address
			curr_csaddr += temp_int; //real current starting address
			strcpy(temp, "\0\0\0\0\0\0");

			
			strncpy(temp, line+7, 2);
			temp[2]='\0';
			temp_int = strtol(temp, NULL, 16); //length
			length = temp_int; //real current line length
			strcpy(temp, "\0");

			for(int i=0;i<length;i++){
				strncpy(temp, line+9+(i*2), 2);
				temp_int = strtol(temp, NULL, 16);
				//printf("[%04X] %02X\n", curr_csaddr+i, temp_int);
				((uint8_t*)memory)[curr_csaddr+i] = temp_int;
				//printf("[%04X] %02X\n", curr_csaddr+i, ((uint8_t*)memory)[curr_csaddr+i]);
				strcpy(temp, "\0");
			}//printf("\n");
		}
		else if(line[0] == 'M'){
			int modify_address = csaddr;
			int modify_byte = 0;
			int modify_sign = 0;
			int modify_index = 0;
			strncpy(temp, line+1, 6);
			temp_int = strtol(temp, NULL, 16);
			modify_address += temp_int; //modify address
			strcpy(temp, "\0\0\0\0\0\0");

			strncpy(temp, line+7, 2);
			temp[2] = '\0';
			temp_int = strtol(temp, NULL, 16);
			modify_byte = temp_int; //bytes for modify
			strcpy(temp, "\0");

			strncpy(temp, line+9, 1);
			temp[1] = '\0';
			if(temp[0] == '+') modify_sign = 0; //add
			else modify_sign = 1; //sub
			strcpy(temp, "\0");

			strncpy(temp, line+10, 2);
			temp[2] = '\0';
			temp_int = strtol(temp, NULL, 10);
			modify_index = temp_int; //array index
			strcpy(temp, "\0");

			char modify_word[20];
			char modify_temp[20];
			int modify_word_int=0;
			char odd_first;
			char modify_result[20];
			int modify_result_int;
			char modify_result_temp[20];
			sprintf(modify_temp, "%02X", ((uint8_t*)memory)[modify_address]);
			strcat(modify_word, modify_temp);
			//printf("1modify_word: %s\n", modify_word);
			sprintf(modify_temp, "%02X", ((uint8_t*)memory)[modify_address+1]);
			strcat(modify_word, modify_temp);
			//printf("2modify_word: %s\n", modify_word);
			sprintf(modify_temp, "%02X", ((uint8_t*)memory)[modify_address+2]);
			strcat(modify_word, modify_temp);
			//printf("3modify_word: %s\n\n", modify_word);

			if(modify_byte%2 != 0){
				odd_first = modify_word[0];
				modify_word[0] = '0';
			}
			modify_word_int = strtol(modify_word, NULL, 16);

			//printf("%s에 %04X더한다/뺀다.(%d)\n", modify_word, ref_array[modify_index], modify_sign);
			if(modify_sign == 0){
				//+
				modify_word_int += ref_array[modify_index];
			}
			else{
				//-
				modify_word_int -= ref_array[modify_index];
			}

			sprintf(modify_result, "%06X", modify_word_int);
			if(modify_byte%2 != 0){
				modify_result[0]=odd_first;
			}

			
			if(strlen(modify_result) > 6){
				//modify_result[0]='0';
				for(unsigned int i=0;i<strlen(modify_result)-6;i++){
					//modify_result[i]='0';
					for(unsigned int j=0;j<strlen(modify_result)-1;j++){
						modify_result[j] = modify_result[j+1];
					}
				}
			}
			//printf("modify result: %s\n", modify_result);
			strncpy(modify_result_temp, modify_result, 2);
			modify_result_int = strtol(modify_result_temp, NULL, 16);
			((uint8_t*)memory)[modify_address] = modify_result_int;

			strncpy(modify_result_temp, modify_result+2, 2);
			modify_result_int = strtol(modify_result_temp, NULL, 16);
			((uint8_t*)memory)[modify_address+1] = modify_result_int;

			strncpy(modify_result_temp, modify_result+4, 2);
			modify_result_int = strtol(modify_result_temp, NULL, 16);
			((uint8_t*)memory)[modify_address+2] = modify_result_int;


			for(int i=0;i<20;i++){
				modify_word[i] = '\0';
				modify_temp[i] = '\0';
				modify_result[i] = '\0';
				modify_result_temp[i] = '\0';
			}
			//printf("%04X부터 %02Xbytes에 %04X를 더한다/뺀다.(%d)\n", modify_address, modify_byte, ref_array[modify_index], modify_sign);
		}
		else if(line[0] == 'E'){
		
		}
	}

	/*for(int i=0;i<6;i++){
		printf("[%d] %04X\n", i, ref_array[i]);
	}
	printf("\n");*/

	fclose(fp);
	return 0;
}





/* search symbol from symtab */
int search_symtab(char* symbol_name){
	for(int i=0;i<symtab_index;i++){
		if(strcmp(symtab[i].control_section, symbol_name)==0 || (strcmp(symtab[i].symbol_name, symbol_name) == 0)){
			return symtab[i].address; //duplicate
		}
	}
	return -1; //new
}





/* print symtab */
int print_symtab(){
	int total_length=0;
	printf("control\tsymbol\taddress\tlength\n");
	printf("section\tname\n");
	printf("---------------------------------\n");
	for(int i=0;i<symtab_index;i++){
		/*printf("control section: %s\n", symtab[i].control_section);
		printf("symbol name: %s\n", symtab[i].symbol_name);
		printf("address: %04X\n", symtab[i].address);
		printf("length: %04X\n", symtab[i].length);
		printf("=========================\n");*/
		if(strcmp(symtab[i].control_section, "\0")!=0){
			printf("%s\t\t%04X\t%04X\n", symtab[i].control_section, symtab[i].address, symtab[i].length);
			total_length += symtab[i].length;
		}
		else{
			printf("\t%s\t%04X\n", symtab[i].symbol_name, symtab[i].address);
		}
	}
	printf("---------------------------------\n");
	printf("\ttotal length %04X\n", total_length);
	regL = total_length;
	program_length = total_length;
	return 0;
}





/* create breakpoint */
int create_breakpoint(char* point){
	int breakpoint_int;
	breakpoint_int = strtol(point, NULL, 16);
	breakpoint[breakpoint_num++] = breakpoint_int;
	printf("\t\t[ok] create breakpoint %s\n", point);
	return 0;
}




/* run
   condition_code: =(0), <(1), >(2)
 */
int run(){
	//((uint8_t*)memory)[i]
	char word[20];
	char temp[20];
	int target_address;

while(regPC < program_length){
	/* setting other register content and condition code */
	if(((uint8_t*)memory)[regPC] == 0x69){
		//LDB(regB, immediate)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		target_address += (regPC+3);
		regB = target_address;
	}
	else if(((uint8_t*)memory)[regPC] == 0x03){
		//LDA(regA)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		target_address += (regPC+3);

		char LDA[10];
		char LDA_temp[10];
		int LDA_int;
		sprintf(LDA_temp, "%02X", ((uint8_t*)memory)[target_address]);
		strcat(LDA, LDA_temp);
		sprintf(LDA_temp, "%02X", ((uint8_t*)memory)[target_address+1]);
		strcat(LDA, LDA_temp);
		sprintf(LDA_temp, "%02X", ((uint8_t*)memory)[target_address+2]);
		strcat(LDA, LDA_temp);
		LDA_int = strtol(LDA, NULL, 16);
		regA = LDA_int;

		//regA = ((uint8_t*)memory)[target_address];
		//printf("regA: %06X\n", regA);
	}
	else if(((uint8_t*)memory)[regPC] == 0x01){
		//LDA(regA, immediate)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		regA = target_address;
	}
	else if(((uint8_t*)memory)[regPC] == 0x53){
		//LDCH(regA, base relative, index addressing)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		target_address += regB;
		target_address += regX;
		//printf("target address: %06X\n", target_address);
		//printf("memory[%d]: %02X\n", regX, ((uint8_t*)memory)[target_address]);
		regA = ((uint8_t*)memory)[target_address];
		//printf("regA by LDCH: %06X(%06X)\n", regA, regX);
	}
	else if(((uint8_t*)memory)[regPC] == 0xB4){
		//CLEAR(register=0)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		word[1]='\0';
		target_address = strtol(word, NULL, 16);
		if(target_address == 0) regA = 0;
		else if(target_address == 1) regX = 0;
		else if(target_address == 2) regL = 0;
		else if(target_address == 3) regB = 0;
		else if(target_address == 4) regS = 0;
		else if(target_address == 5) regT = 0;
		else if(target_address == 8) regPC = 0;
		//printf("CLEAR\n");
	}
	else if(((uint8_t*)memory)[regPC] == 0x75){
		//LDT(regT, format:4, immediate)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+3]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		regT = target_address;
		//printf("regT: %06X\n", regT);
	}
	else if(((uint8_t*)memory)[regPC] == 0x77){
		//LDT(regT, base relative)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		target_address += regB;
		//printf("target address: %06X\n", target_address);
		//printf("memory: %02X\n", ((uint8_t*)memory)[target_address]);
		//printf("memory: %02X\n", ((uint8_t*)memory)[target_address+1]);
		//printf("memory: %02X\n", ((uint8_t*)memory)[target_address+2]);

		char LDT[10];
		char LDT_temp[10];
		for(int i=0;i<10;i++){
			LDT[i]='\0';
			LDT_temp[i]='\0';
		}
		int LDT_int;
		sprintf(LDT_temp, "%02X", ((uint8_t*)memory)[target_address]);
		strcat(LDT, LDT_temp);
		sprintf(LDT_temp, "%02X", ((uint8_t*)memory)[target_address+1]);
		strcat(LDT, LDT_temp);
		sprintf(LDT_temp, "%02X", ((uint8_t*)memory)[target_address+2]);
		strcat(LDT, LDT_temp);
		LDT_int = strtol(LDT, NULL, 16);
		regT = LDT_int;

		//printf("LDT: %s\n", LDT);
		//printf("LDT_int: %06X\n", LDT_int);
		//printf("regT: %06X\n", regT);

		//regT = ((uint8_t*)memory)[target_address];
	}
	else if(((uint8_t*)memory)[regPC] == 0xE3){
		//TD(condition_code)
		condition_code = 1;
	}
	else if(((uint8_t*)memory)[regPC] == 0xDB){
		//RD(condition_code)
		condition_code = 0;
	}
	else if(((uint8_t*)memory)[regPC] == 0x29){
		//COMP(condition_code, compare with A, immediate)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		if(regA == target_address){
			condition_code = 0;
		}else if(regA < target_address){
			condition_code = 1;
		}else{
			condition_code = 2;
		}
	}
	/*else if(((uint8_t*)memory)[regPC] == 0xA0){
		//COMPR(condition_code)
	}*/
	else if(((uint8_t*)memory)[regPC] == 0xB8){
		//TIXR(condition_code, compare with X)
		int reg;
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		word[1]='\0';
		target_address = strtol(word, NULL, 16);
		if(target_address == 0) reg=regA;
		else if(target_address == 1) reg=regX;
		else if(target_address == 2) reg=regL;
		else if(target_address == 3) reg=regB;
		else if(target_address == 4) reg=regS;
		else if(target_address == 5) reg=regT;
		else if(target_address == 8) reg=regPC;

		regX++;
		if(regX < reg){
			condition_code = 1;
		}else if(regX == reg){
			condition_code = 0;
		}else{
			condition_code = 2;
		}
	}
	else if(((uint8_t*)memory)[regPC] == 0x17){
		//STL
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		target_address += (regPC+3);
		
		char STL[10];
		char STL_temp[10];
		for(int i=0;i<10;i++){
			STL[i]='\0';
			STL_temp[i]='\0';
		}
		int STL_int;
		sprintf(STL, "%06X", regL);
		strncpy(STL_temp, STL, 2);
		STL_int = strtol(STL_temp, NULL, 16);
		((uint8_t*)memory)[target_address] = STL_int;
		strncpy(STL_temp, STL+2, 2);
		STL_int = strtol(STL_temp, NULL, 16);
		((uint8_t*)memory)[target_address+1] = STL_int;
		strncpy(STL_temp, STL+4, 2);
		STL_int = strtol(STL_temp, NULL, 16);
		((uint8_t*)memory)[target_address+2] = STL_int;

		//((uint8_t*)memory)[target_address] = regL;
	}
	else if(((uint8_t*)memory)[regPC] == 0x0F){
		//STA
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		target_address += (regPC+3);

		char STA[10];
		char STA_temp[10];
		for(int i=0;i<10;i++){
			STA[i]='\0';
			STA_temp[i]='\0';
		}
		int STA_int;
		sprintf(STA, "%06X", regA);
		//printf("STA: %s\n", STA);
		strncpy(STA_temp, STA, 2);
		STA_int = strtol(STA_temp, NULL, 16);
		((uint8_t*)memory)[target_address] = STA_int;
		strncpy(STA_temp, STA+2, 2);
		STA_int = strtol(STA_temp, NULL, 16);
		((uint8_t*)memory)[target_address+1] = STA_int;
		strncpy(STA_temp, STA+4, 2);
		STA_int = strtol(STA_temp, NULL, 16);
		((uint8_t*)memory)[target_address+2] = STA_int;

		//((uint8_t*)memory)[target_address] = regA;
	}
	else if(((uint8_t*)memory)[regPC] == 0x13){
		//STX(base relative)
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		word[0] = '0';
		target_address = strtol(word, NULL, 16);
		target_address += regB;

		char STX[10];
		char STX_temp[10];
		for(int i=0;i<10;i++){
			STX[i]='\0';
			STX_temp[i]='\0';
		}
		int STX_int;
		sprintf(STX, "%06X", regX);
		strncpy(STX_temp, STX, 2);
		STX_int = strtol(STX_temp, NULL, 16);
		((uint8_t*)memory)[target_address] = STX_int;
		strncpy(STX_temp, STX+2, 2);
		STX_int = strtol(STX_temp, NULL, 16);
		((uint8_t*)memory)[target_address+1] = STX_int;
		strncpy(STX_temp, STX+4, 2);
		STX_int = strtol(STX_temp, NULL, 16);
		((uint8_t*)memory)[target_address+2] = STX_int;

		//((uint8_t*)memory)[target_address] = regX;
	}

	for(int i=0;i<20;i++){
		word[i] = '\0';
		temp[i] = '\0';
	}

	/* setting register PC according to each jump instruction */
	if(((uint8_t*)memory)[regPC] == 0x4B){
		//JSUB(format: 4) 
		regL = regPC + 4;
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
		strcat(word, temp);
		sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+3]);
		strcat(word, temp);
		word[0] = '0';
		regPC = strtol(word, NULL, 16);
	}
	else if(((uint8_t*)memory)[regPC] == 0x33){
		//JEQ
		if(condition_code == 0){
			sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
			strcat(word, temp);
			sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
			strcat(word, temp);
			word[0] = '0';
			regPC += 3;
			regPC += strtol(word, NULL, 16);
		}
		else{
			regPC += 3;
		}
	}
	else if(((uint8_t*)memory)[regPC] == 0x4F){
		//RSUB
		regPC = regL;
		//printf("return subroutine to %06X\n", regL);
	}
	else if(((uint8_t*)memory)[regPC] == 0x3B){
		//JLT
		if(condition_code == 1){
			sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+1]);
			strcat(word, temp);
			sprintf(temp, "%02X", ((uint8_t*)memory)[regPC+2]);
			strcat(word, temp);
			word[0] = '0';
			regPC += 3;
			int convert16 = 0xFFF;
			convert16 -= strtol(word, NULL, 16);
			convert16++;
			regPC -= convert16;
			//regPC += strtol(word, NULL, 16);
		}
		else{
			regPC += 3;
		}
	}
	else if(((uint8_t*)memory)[regPC] == 0x3E){
		//J(In this case, only jump to program's end)
		regPC = program_length;
	}
	else if(((uint8_t*)memory)[regPC] == 0x75){
		//LDT(format: 4)
		regPC += 4;
	}
	else if(((uint8_t*)memory)[regPC] == 0xB4 || ((uint8_t*)memory)[regPC] == 0xB8 || ((uint8_t*)memory)[regPC] == 0xA0){
		//CLEAR, TIXR(foramt: 2)
		regPC += 2;
	}
	else{
		//normal(foramt: 3)
		regPC += 3;
	}
	//printf("PC: %06X\n", regPC);
	for(int i=0;i<20;i++){
		word[i] = '\0';
		temp[i] = '\0';
	}
	//printf("regPC: %06X\n", regPC);
	if(find_breakpoint(regPC) == 0) break;
}
	
	printf("A : %06X\t X : %06X\n", regA, regX);
	printf("L : %06X\tPC : %06X\n", regL, regPC);
	printf("B : %06X\t S : %06X\n", regB, regS);
	printf("T : %06X\n", regT);
	if(regPC == program_length) printf("\t\tEnd program\n");
	else printf("\t\tStop at checkpoint[%X]\n", regPC);
	return 0;
}



/* find breakpoint */
int find_breakpoint(int point){
	for(int i=0;i<breakpoint_num;i++){
		if(breakpoint[i]==point) return 0; //is breakpoint
	}
	return 1; //not breakpoint
}
