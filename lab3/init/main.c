#include <stdio.h>
#include <sched.h>

#define TASK(N) \
/* state etc */	{ 0, N * 10, N * 10, N, \
/* todo tss */    {(uint64_t)idle, 0, stacks + N * PAGE_SIZE, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0 \
				  } \
                }

void task_initialize();
void create_process(int n);

struct task_struct t[4] = {TASK(1), TASK(2), TASK(3), TASK(4)}

void start_kernel()
{
    printf("[S] ZJU OS Lab 2             ID:3170101209\n");
    task_initialize();
}

void task_initialize()
{
    for(int i = 1; i <= 4; ++i)
        task[i] = &t[i-1];
}
