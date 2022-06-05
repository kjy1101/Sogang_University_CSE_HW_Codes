#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "lib/user/syscall.h"
#include "devices/shutdown.h"
#include "userprog/process.h"
#include "devices/input.h"
#include "threads/vaddr.h"
#include "threads/synch.h"
#include <string.h>

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  //printf ("system call!\n");
  //printf("system call number : %d\n", *(uint32_t*)(f->esp));
	int system_call_number = *(uint32_t*)f->esp;
	uint32_t *arg1 = (uint32_t*)(f->esp+4);
	uint32_t *arg2 = (uint32_t*)(f->esp+8);
	uint32_t *arg3 = (uint32_t*)(f->esp+12);
	uint32_t *arg4 = (uint32_t*)(f->esp+16);
	int valid_flag = 0;

	valid_flag = check_address_validity(arg1);
	if(valid_flag == -1){
		exit(-1);
	}

	if(system_call_number == SYS_HALT){
		halt();
	}else if(system_call_number == SYS_EXIT){
		exit(*arg1);
	}else if(system_call_number == SYS_EXEC){
		f->eax = exec((const char*)*arg1);
	}else if(system_call_number == SYS_WAIT){
		f->eax = wait((pid_t)*arg1);
	}else if(system_call_number == SYS_READ){
		f->eax = read(*arg1, (void*)*arg2, *arg3);
	}else if(system_call_number == SYS_WRITE){
		f->eax = write(*arg1, (const void*)*arg2, *arg3);
	}else if(system_call_number == SYS_FIBONACCI){
		fibonacci(*arg1);
	}else if(system_call_number == SYS_MAX_OF_FOUR_INT){
		max_of_four_int(*arg1, *arg2, *arg3, *arg4);
	}else{
		exit(-1);
	}
  //thread_exit ();
}

void halt(void){
	shutdown_power_off();
}

void exit(int status){
	struct thread *t = thread_current();
	t->exit_status = status;
	printf("%s: exit(%d)\n", t->name, t->exit_status);
	thread_exit();
}

pid_t exec(const char *cmd_line){
	int pid = process_execute(cmd_line);
	return pid;
}

int wait(pid_t pid){
	return process_wait(pid);
}

int read(int fd, void *buffer, unsigned size){
	if(fd == 0){
		for(unsigned count=size;count>0;count--){
			*((char*)buffer++) = input_getc();
		}
		return size;
	}
	else return -1;
}

int write(int fd, const void *buffer, unsigned size){
	if(fd == 1){
		putbuf(buffer, size);
		return size;
	}
	else return -1;
}

int check_address_validity(const void *vaddr){
	if(is_user_vaddr(vaddr)!=true)
		return -1;
	return 0;
}

int fibonacci(int n){
	int temp=0;
	int temp1=0, temp2=1;
	for(int i=1;i<=n;++i){
		temp = temp1 + temp2;
		temp1 = temp2;
		temp2 = temp;
	}
	printf("%d ", temp1);
	return 0;
}

int max_of_four_int(int n1, int n2, int n3, int n4){
	int max = n1;
	if(max < n2) max = n2;
	if(max < n3) max = n3;
	if(max < n4) max = n4;
	printf("%d\n", max);
	return 0;
}
