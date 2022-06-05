/* $begin shellmain */
#include "csapp.h"
#include<errno.h>
#define MAXARGS   128
#define STA_EXIT 99

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void sigint_handler(int sig);

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
	pid_t ppid;
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv); 
    if (argv[0] == NULL)  
		return;   /* Ignore empty lines */

    if (!builtin_command(argv)) { //quit -> exit(0), & -> ignore, other -> run
		//printf("(maybe-parent)PID: %ld\n", getpid());
		if((pid = Fork())==0){ /* Child runs user job */
			//printf("(maybe-child)PID: %ld\n", getpid());
			if(!strcmp(argv[0], "exit")){
				ppid = getppid();
				kill(ppid, SIGINT);
				exit(0);
				//exit(STA_EXIT);
			}
        	if (execvp(argv[0], argv) < 0) {	//ex) /bin/ls ls -al &
           		printf("%s: Command not found.\n", argv[0]);
            	exit(0);
        	}
		}

		/* Parent waits for foreground job to terminate */
		if (!bg){ 
		    int status;
			if(waitpid(pid, &status, 0) < 0){
				unix_error("waitfg: waitpid error");
			}/*else{
				if(WEXITSTATUS(status) == STA_EXIT){
					exit(1);
				}
			}*/
		}
		else//when there is backgrount process!
		    printf("%d %s", pid, cmdline);
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
