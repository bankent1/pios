#ifndef __MM_H
#define __MM_H

typedef struct PTE {
	u32 incore: 1;
	u32 read: 1;
	u32 write: 1;
	u32 frame: 29;
} PTE;

// error codes
#define MEM_OK 0
#define MEM_ALREADY_INIT 1
#define MEM_NOT_INIT 2

int mem_init();
int mem_shutdown();
int mem_allocate_pt(int pid);
int mem_free_pt(int pid);
int mem_get_pt(int pid, PTE **table);


#endif