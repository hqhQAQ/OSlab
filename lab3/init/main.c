#include <stdio.h>
#include <sched.h>
#include <syscall.h>

void process();

#define TASK(N) \
/* state etc */	{ 0, 5, N * 10, N, 0, 0,\
/* todo tss */    {(uint64_t)process, 0, (uint64_t)STACK + (N + 2) * PAGE_SIZE, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0 \
				  } \
                }

void task_initialize();

struct task_struct t[4] = {TASK(1), TASK(2), TASK(3), TASK(4)};

void start_kernel()
{
    printf("[S] ZJU OS Lab 2             ID:3170101209\n");
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
    printf("[PID = %d] Process Create Successfully!\n", current->pid);
    while(1) {
        printf("[PID = %d] Context Calculation: count++ = %d\n", current->pid, count++);
        for(int i = 0; i < 80000000; i++);
    }
}
