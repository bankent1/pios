#ifndef __PROC_H
#define __PROC_H

#include <kint.h>

typedef u32 pid_t;
typedef u8 tag_t;

enum ProcState {
	STATE_RUNNING,
	STATE_BLOCKED,
	STATE_READY,
};

#define TAG_KERNEL 0
#define TAG_USER 1

#define PROC_MAX_NAME 24
#define PROC_MAX_PID 2048 // 2^11
#define PROC_LOWEST_PRIORITY 6

// error codes
#define PROC_OK 0
#define PROC_ALREADY_INIT 1
#define PROC_NEVER_INIT 2
#define PROC_NULL_FUNC 3
#define PROC_BAD_TAG 4
#define PROC_BAD_PRIORITY 5
#define PROC_NULL_NAME 6
#define PROC_OUT_OF_PIDS 7

// func prototypes
int proc_init();
int proc_shutdown();
int proc_create(char *name, int (*funct)(void*), void *args, int priority, tag_t tag, pid_t *pid);
int proc_free(pid_t pid);
int proc_quit(int status);
int proc_switch(pid_t new_proc);
void proc_kill();

#endif