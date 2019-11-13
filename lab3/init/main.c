#include <stdio.h>
#include <sched.h>
#include <syscall.h>

void process();

#ifdef PREEMPTIVE
#define TASK(N) \
/* state etc */	{ 0, 5, N * 10, N, 0, 0, N, \
/* todo tss */    {(uint64_t)process, 0, (uint64_t)stacks + (N + 2) * PAGE_SIZE, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0 \
				  } \
                }
#else
#define TASK(N) \
/* state etc */	{ 0, 5, N * 10, N, 0, 0, \
/* todo tss */    {(uint64_t)process, 0, (uint64_t)stacks + (N + 2) * PAGE_SIZE, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0 \
				  } \
                }
#endif

void task_initialize();

struct task_struct t[4] = {TASK(1), TASK(2), TASK(3), TASK(4)};

void start_kernel()
{
    printf("\e[33m[S] ZJU OS Lab 3             ID:3170101209\n\e[0m");
    task_initialize();
    idle();
}

void task_initialize()
{
    for(int i = 1; i <= 4; ++i) {
        task[i] = &t[i-1];
    }
}

void process()
{
    int count = 0;
    printf("\e[32m[PID = %d] Process Create Successfully!\e[0m\n", current->pid);
    while(1) {
        printf("\e[32m[PID = %d] Context Calculation: count++ = %d\e[0m\n", current->pid, count++);
        for(int i = 0; i < 80000000; i++);
    }
}
