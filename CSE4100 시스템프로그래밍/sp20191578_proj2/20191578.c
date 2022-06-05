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
