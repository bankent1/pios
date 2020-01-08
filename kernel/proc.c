/*
 * proc.c
 *
 * Travis Banken
 * 1/6/2020
 * 
 * Framework for process management
 */

#include <proc.h>
#include <kdebug.h>
#include <ktools.h>
#include <kint.h>
#include <string.h>

typedef struct Regs {
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r4;
    u32 r5;
    u32 r6;
    u32 r7;
    u32 r8;
    u32 r9;
    u32 r10;
    u32 r11;
    u32 cpsr;
    u32 sp;
    u32 lr;
} Regs;

typedef struct ProcChildren {
    pid_t pid;
    struct ProcChildren *next;
} ProcChildren;

typedef struct PCB {
    pid_t           pid;
    Regs            regs;
    u8              *stack;
    u64             cpu_time;
    char            name[PROC_MAX_NAME+1];
    int             (*start_func)(void*);
    void            *args;
    kbool           free;
    enum ProcState  state;
    pid_t           parent;
    int             num_children;
    int             num_children_quit;
    ProcChildren    *children;
    int             status;
    int             priority;
    tag_t           tag;
    // TODO sid
} PCB;
static PCB procs[PROC_MAX_PID+1];

static pid_t cur_pid = 0;
static kbool proc_initialized = FALSE;

static int launch()
{
    int rc = procs[cur_pid].start_func(procs[cur_pid].args);
    proc_quit(rc);
    return 0;
}

int proc_init()
{
    KLOG("Process Init called!\n");
    kcheckmode();

    if (proc_initialized) {
        KLOG("Already Initialized!\n");
        return PROC_ALREADY_INIT;
    }

    // TODO
    
    proc_initialized = TRUE;

    return PROC_OK;
}

int proc_shutdown()
{
    KLOG("Process Shutdown Called!\n");
    kcheckmode();

    if (!proc_initialized) {
        KLOG("ERROR -- Never Initialized!\n");
        return PROC_NEVER_INIT;
    }

    // TODO

    proc_initialized = FALSE;
    return PROC_OK;
}

int proc_create(char *name, int (*funct)(void*), void *args, int priority, tag_t tag, pid_t *pid)
{
    kcheckmode();

    if (funct == NULL) {
        KLOG("ERROR -- func is null\n");
        return PROC_NULL_FUNC;
    }
    if (tag != TAG_KERNEL || tag != TAG_USER) {
        KLOG("ERROR -- invalid tag %d\n", tag);
        return PROC_BAD_TAG;
    }
    if (priority < 0 || priority > PROC_LOWEST_PRIORITY) {
        KLOG("ERROR -- Bad priority %d\n", priority);
        return PROC_BAD_PRIORITY;
    }
    if (name == NULL) {
        return PROC_NULL_NAME;
    }

    kbool found = FALSE;
    for (int i = 0; i <= PROC_MAX_PID; i++) {
        if (procs[i].free) {
            found = TRUE;
            *pid = i;
            // TODO
        }
    }
    if (!found) {
        KLOG("ERROR -- Out of pids!\n");
        return PROC_OUT_OF_PIDS;
    }

    // fill in PCB
    procs[*pid].pid = *pid;
    procs[*pid].stack = NULL; // TODO
    procs[*pid].cpu_time = 0;
    strncpy(procs[*pid].name, name, PROC_MAX_NAME);
    procs[*pid].start_func = launch;
    procs[*pid].args = args;
    procs[*pid].free = FALSE;
    procs[*pid].state = STATE_READY;
    procs[*pid].parent = cur_pid;
    procs[*pid].num_children = 0;
    procs[*pid].num_children_quit = 0;
    procs[*pid].children = NULL;
    procs[*pid].status = 0;
    procs[*pid].priority = priority;
    procs[*pid].tag = tag;

    // update parent PCB
    // TODO


    if (*pid == 0) {
        KLOG("First process, switching to %s\n", name);
        // TODO
        // dispatch
    }

    return PROC_OK;
}

int proc_free(pid_t pid)
{
    (void) pid;
    kcheckmode();
    return PROC_OK;
}

int proc_quit(int status)
{
    (void) status;
    kcheckmode();
    return PROC_OK;
}

int proc_switch(pid_t new_proc)
{
    (void) new_proc;
    kcheckmode();
    return PROC_OK;
}

void proc_kill()
{
    kcheckmode();
    // TODO
    KLOG("Killing proc %d\n", cur_pid);
}