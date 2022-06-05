/* $begin shellmain */
#include "csapp.h"
#include<errno.h>
#define MAXARGS   128
#define STAT_EXIT 99

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void sigint_handler(int sig);
int is_it_pipeline(char **argv);
int parse_cmd(char **argv, char **cmd1, char **cmd2, char **cmd3, char **cmd4, int pipe_num);

int main() 
{
    char cmdline[MAXLINE]; /* Command line */
	/* Install the SIGINT handler */
	if(signal(SIGINT, sigint_handler) == SIG_ERR)
		unix_error("signal error");

    while (1) {
		/* Read */
		printf("CSE4100:P4-myshell> ");                   
		if(!fgets(cmdline, MAXLINE, stdin)){
			printf("Fail to read\n");
		}
		if (feof(stdin))
		    exit(0);

		/* Evaluate */
		eval(cmdline);
    } 
}
/* $end shellmain */
  
/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    pid_t ppid;           /* Process id */
	pid_t pid2;
	pid_t pid3;
	pid_t pid4;
	int fd[2];			 /* File descriptor */
	int fd2[2];			 /* File descriptor */
	int fd3[2];			 /* File descriptor */
    char *cmd1[MAXARGS];
    char *cmd2[MAXARGS];
    char *cmd3[MAXARGS];
    char *cmd4[MAXARGS];
	int status;
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)  
		return;   /* Ignore empty lines */


    if (!builtin_command(argv)) { //quit -> exit(0), & -> ignore, other -> run

		//printf("파이프 %d개 필요\n", is_it_pipeline(argv));

		int pipe_num = is_it_pipeline(argv);
		if(pipe_num > 0){
			/* Pipeline */
			parse_cmd(argv, cmd1, cmd2, cmd3, cmd4, pipe_num);
			if(pipe_num == 1){
				/* 파이프 1개 생성 */
				if(pipe(fd) < 0){
					printf("pipe error\n");
					exit(1);
				}

				/* 첫번째 Child process 생성 */
				if((pid = Fork()) == 0){
					/* Child */
					//printf("Child1\n");
					close(STDOUT_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					//close(fd[0]);
					if(execvp(cmd1[0], cmd1) < 0){
   	        			printf("%s: Command not found.\n", cmd1[0]);
            			exit(0);
					}
					exit(1);
				}
				close(fd[1]);
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
				/* 두번째 Child process 생성 */
				if((pid2 = Fork()) == 0){
					/* Child */
					//printf("Child2\n");
					close(STDIN_FILENO);
					dup2(fd[0], STDIN_FILENO);
					close(fd[0]);
					close(fd[1]);
					if(execvp(cmd2[0], cmd2) < 0){
   	       	 			printf("%s: Command not found.\n", cmd2[0]);
           	 			exit(0);
					}
					exit(2);
				}
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
			}
			else if(pipe_num == 2){
				/* 파이프 2개 생성 */
				if(pipe(fd) < 0){
					printf("pipe error\n");
					exit(1);
				}
				if(pipe(fd2) < 0){
					printf("pipe error\n");
					exit(1);
				}
				/* 첫번째 Child process 생성 */
				if((pid = Fork()) == 0){
					/* Child */
					close(STDOUT_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					if(execvp(cmd1[0], cmd1) < 0){
   	        			printf("%s: Command not found.\n", cmd1[0]);
            			exit(0);
					}
					exit(1);
				}
				close(fd[1]);
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
				/* 두번째 Child process 생성 */
				if((pid2 = Fork()) == 0){
					/* Child */
					close(STDIN_FILENO);
					close(STDOUT_FILENO);
					dup2(fd[0], STDIN_FILENO);
					dup2(fd2[1], STDOUT_FILENO);
					close(fd[0]);
					close(fd2[1]);
					if(execvp(cmd2[0], cmd2) < 0){
   	        			printf("%s: Command not found.\n", cmd2[0]);
            			exit(0);
					}
					exit(1);
				}
				close(fd2[1]);
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
				/* 세번째 Child process 생성 */
				if((pid3 = Fork()) == 0){
					/* Child */
					//printf("Child2\n");
					close(STDIN_FILENO);
					dup2(fd2[0], STDIN_FILENO);
					close(fd2[0]);
					close(fd2[1]);
					if(execvp(cmd3[0], cmd3) < 0){
   	       	 			printf("%s: Command not found.\n", cmd3[0]);
           	 			exit(0);
					}
					exit(3);
				}
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
			}
			else{
				/* 파이프 3개 생성 */
				if(pipe(fd) < 0){
					printf("pipe error\n");
					exit(1);
				}
				if(pipe(fd2) < 0){
					printf("pipe error\n");
					exit(1);
				}
				if(pipe(fd3) < 0){
					printf("pipe error\n");
					exit(1);
				}
				/* 첫번째 Child process 생성 */
				if((pid = Fork()) == 0){
					/* Child */
					close(STDOUT_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					if(execvp(cmd1[0], cmd1) < 0){
   	        			printf("%s: Command not found.\n", cmd1[0]);
            			exit(0);
					}
					exit(1);
				}
				close(fd[1]);
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
				/* 두번째 Child process 생성 */
				if((pid2 = Fork()) == 0){
					/* Child */
					close(STDIN_FILENO);
					close(STDOUT_FILENO);
					dup2(fd[0], STDIN_FILENO);
					dup2(fd2[1], STDOUT_FILENO);
					close(fd[0]);
					close(fd2[1]);
					if(execvp(cmd2[0], cmd2) < 0){
   	        			printf("%s: Command not found.\n", cmd2[0]);
            			exit(0);
					}
					exit(2);
				}
				close(fd2[1]);
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
				/* 세번째 Child process 생성 */
				if((pid3 = Fork()) == 0){
					/* Child */
					close(STDIN_FILENO);
					close(STDOUT_FILENO);
					dup2(fd2[0], STDIN_FILENO);
					dup2(fd3[1], STDOUT_FILENO);
					close(fd2[0]);
					close(fd3[1]);
					if(execvp(cmd3[0], cmd3) < 0){
   	        			printf("%s: Command not found.\n", cmd3[0]);
            			exit(0);
					}
					exit(1);
				}
				close(fd3[1]);
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(3);
				}
				/* 네번째 Child process 생성 */
				if((pid4 = Fork()) == 0){
					/* Child */
					//printf("Child2\n");
					close(STDIN_FILENO);
					dup2(fd3[0], STDIN_FILENO);
					close(fd3[0]);
					close(fd3[1]);
					if(execvp(cmd4[0], cmd4) < 0){
   	       	 			printf("%s: Command not found.\n", cmd4[0]);
           	 			exit(0);
					}
					exit(4);
				}
				wait(&status);
				if(WIFSIGNALED(status) || WIFSTOPPED(status)){
					exit(1);
				}
			}
		}
		else{
			/* Not Pipeline */
			if((pid = Fork())==0){ /* Child runs user job */
				if(!strcmp(argv[0], "exit")){
					ppid = getppid();
					kill(ppid, SIGINT);
					exit(0);
					//exit(STAT_EXIT);
				}
   	     		if (execvp(argv[0], argv) < 0) {	//ex) /bin/ls ls -al &
   	        		printf("%s: Command not found.\n", argv[0]);
            		exit(0);
        		}
			}
			//int status;
			if(!bg){
				if(waitpid(pid, &status, 0) < 0){
					unix_error("waitfg: waitpid error");
				}/*else{
					if(WEXITSTATUS(status) == STAT_EXIT){
						exit(1);
					}
				}*/
			}
			else{
				printf("%d %s", pid, cmdline);
			}
		}

		/* Parent waits for foreground job to terminate */
		//if (!bg){ 
		    //int status;
			/*if(waitpid(pid, &status, 0) < 0){
				unix_error("waitfg: waitpid error");
			}else{
				if(WEXITSTATUS(status) == STAT_EXIT){
					exit(1);
				}
			}
			if(pid2 > 0){
				//printf("send kill signal to pid2 %d\n", pid2);
				//kill(pid2, SIGINT);
				if(waitpid(pid2, &status, 0) < 0){
					unix_error("waitfg: waitpid error");
				}
			}	*/
		//}
		//else//when there is background process!
		    //printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit")) /* quit command */
	exit(0);  
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
	return 1;
	if (!strcmp(argv[0], "cd")){
		if(argv[1] == NULL){
			if(chdir(getenv("HOME"))){
				printf("Fail to go home\n");
			}
		}else if(argv[1] != NULL){
			if(chdir(argv[1])){
				printf("No directory\n");
			}
		}else{
			printf("USAGE: cd [dir]\n");
		}
		return 1;
	}
    return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}
/* $end parseline */

void sigint_handler(int sig){
	//printf("SIGNAL: Stop the process.\n");
	fflush(stdout);
	exit(0);
}

int is_it_pipeline(char **argv){
	int argc=0;
	int pipe_flag=0;
	while(argv[argc] != NULL){
		for(unsigned int i=0;i<strlen(argv[argc]);i++){
			if(argv[argc][i] == '|'){
				pipe_flag++;
			}
		}
		//printf("%s\n", argv[argc]);
		argc++;
	}
	return pipe_flag;
}


int parse_cmd(char **argv, char **cmd1, char **cmd2, char **cmd3, char **cmd4, int pipe_num){
	/* 명령어 쪼개기 */
	int i;
	int j=0;
	int cmdn[4] = {0,0,0,0};
	if(pipe_num == 1){
		/* 명령어 2개 */
		for(i=0;argv[i]!=NULL;i++){
			if(!strcmp(argv[i], "|")){
				cmd1[i] = NULL;
				break;
			}
			cmd1[i] = argv[i];
			//printf("cmd1[%d]: %s\n", i, cmd1[i]);
		}
		cmdn[0]=i;
		for(i=i+1;argv[i]!=NULL;i++){
			cmd2[j++] = argv[i];
			//printf("cmd2[%d]: %s\n", j-1, cmd2[j-1]);
		}
		cmd2[j] = NULL;
		cmdn[1]=j;
	}else if(pipe_num == 2){
		/* 명령어 3개 */
		for(i=0;argv[i]!=NULL;i++){
			if(!strcmp(argv[i], "|")){
				cmd1[i] = NULL;
				break;
			}
			cmd1[i] = argv[i];
		}
		cmdn[0]=i;
		for(i=i+1;argv[i]!=NULL;i++){
			if(!strcmp(argv[i], "|")){
				cmd2[j] = NULL;
				break;
			}
			cmd2[j++] = argv[i];
		}
		cmdn[1]=j;
		j=0;
		for(i=i+1;argv[i]!=NULL;i++){
			cmd3[j++] = argv[i];
		}
		cmd3[j] = NULL;
		cmdn[2]=j;
	}else{
		/* 명령어 4개 */
		for(i=0;argv[i]!=NULL;i++){
			if(!strcmp(argv[i], "|")){
				cmd1[i] = NULL;
				break;
			}
			cmd1[i] = argv[i];
		}
		cmdn[0]=i;
		for(i=i+1;argv[i]!=NULL;i++){
			if(!strcmp(argv[i], "|")){
				cmd2[j] = NULL;
				break;
			}
			cmd2[j++] = argv[i];
		}
		cmdn[1]=j;
		j=0;
		for(i=i+1;argv[i]!=NULL;i++){
			if(!strcmp(argv[i], "|")){
				cmd3[j] = NULL;
				break;
			}
			cmd3[j++] = argv[i];
		}
		cmdn[2]=j;
		j=0;
		for(i=i+1;argv[i]!=NULL;i++){
			cmd4[j++] = argv[i];
		}
		cmd4[j] = NULL;
		cmdn[3]=j;
	}

	/* 큰따옴표 지우기 */
	if(cmdn[0] > 0){
		/* cmd1 */
		for(int i=0;i<cmdn[0];i++){
			if(cmd1[i][0]=='"'){
				cmd1[i]=cmd1[i]+1;
				cmd1[i][strlen(cmd1[i])-1]='\0';
			}
		}
	}
	if(cmdn[1] > 0){
		/* cmd2 */
		for(int i=0;i<cmdn[1];i++){
			if(cmd2[i][0]=='"'){
				cmd2[i]=cmd2[i]+1;
				cmd2[i][strlen(cmd2[i])-1]='\0';
			}
		}
	}
	if(cmdn[2] > 0){
		/* cmd3 */
		for(int i=0;i<cmdn[2];i++){
			if(cmd3[i][0]=='"'){
				cmd3[i]=cmd3[i]+1;
				cmd3[i][strlen(cmd3[i])-1]='\0';
			}
		}
	}
	if(cmdn[3] > 0){
		/* cmd4 */
		for(int i=0;i<cmdn[3];i++){
			if(cmd4[i][0]=='"'){
				cmd4[i]=cmd4[i]+1;
				cmd4[i][strlen(cmd4[i])-1]='\0';
			}
		}
	}
	return 0;
}
