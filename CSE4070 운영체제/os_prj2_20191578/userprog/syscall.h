#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "lib/user/syscall.h"
void syscall_init (void);

/* project 1 */
void halt(void);
void exit(int status);
pid_t exec(const char *cmd_line);
int wait(pid_t pid);
int check_address_validity(const void *vaddr);
int fibonacci(int n);
int max_of_four_int(int n1, int n2, int n3, int n4);

/* project 2 */
bool create(const char *file, unsigned initial_size);
bool remove(const char *file);
int open(const char *file);
void close(int fd);
int filesize(int fd);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
void seek(int fd, unsigned position);
unsigned tell(int fd);

#endif /* userprog/syscall.h */
