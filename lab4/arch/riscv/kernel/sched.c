#include <sched.h>
#include <stdio.h>
#include <syscall.h>
#include <mm.h>

union task_union {
	struct task_struct task;
	char stack[PAGE_SIZE];
};
static union task_union init_task = { INIT_TASK, };	
struct task_struct * current = &(init_task.task);
struct task_struct * task[NR_TASKS] = {&(init_task.task), };

#ifndef PREEMPTIVE
/*
 *  'schedule()' is the scheduler function. This is GOOD CODE! There
 * probably won't be any reason to change this, as it should work well
 * in all circumstances (ie gives IO-bound processes good response etc).
 * The one thing you might take a look at is the signal-handler code here.
 *
 *   NOTE!!  Task 0 is the 'idle' task, which gets called when no other
 * tasks can run. It can not be killed, and it cannot sleep. The 'state'
 * information in task[0] is never used.
 */
void schedule()
{
	int i,next,c;
	struct task_struct ** p;

/* this is the scheduler proper: */

	while (1) {
		c = -1;
		next = 0;
		i = NR_TASKS;
		p = &task[NR_TASKS];
		while (--i) {
			if (!*--p)
				continue;
			if ((*p)->state == TASK_RUNNING && (*p)->counter > c) {
				c = (*p)->counter;
                next = i;
            }
		}
		if (c) 
            break;
		for(p = &LAST_TASK; p > &FIRST_TASK; --p)
			if (*p)
				(*p)->counter = ((*p)->counter >> 1) + (*p)->priority;
	}	
	printf("\e[34m[!] Switch from task %d to %d, prio: %d, counter: %d\e[0m\n", 
		current->pid, task[next]->pid, task[next]->priority, task[next]->counter);
	switch_to(next);
}
#else
void schedule()
{
	int i,next,c, max_priority;
	struct task_struct ** p;

	while (1) {
		c = -1;
		max_priority = -1;
		next = 0;
		i = NR_TASKS;
		p = &task[NR_TASKS];
		// find the max add_prority with time
		while (--i) {
			if (!*--p)
				continue;
			if ((*p)->state == TASK_RUNNING && (*p)->counter > 0 
					&& (*p)->add_priority > max_priority) {
				max_priority = (*p)->add_priority;
            }
		}
		// printf("maxpriority : %d\n", max_priority);
		i = NR_TASKS;
		p = &task[NR_TASKS];
		while (--i) {
			if (!*--p)
				continue;
			if ((*p)->state == TASK_RUNNING && (*p)->add_priority == max_priority 
					&& (*p)->counter > c) {
				c = (*p)->counter;
                next = i;
            }
		}
		if (c > 0) 
            break;
		for(p = &LAST_TASK; p > &FIRST_TASK; --p)
			if (*p)
				(*p)->counter = ((*p)->counter >> 1) + (*p)->priority;
	}
	uint64_t pc = get_pc();
	printf("\e[34m[!] schedule: pc 0x00000000%04x\e[0m\n", pc);	
	printf("\e[34m[!] Switch from task %d to %d, add_prio: %d, counter: %d\e[0m\n", 
		current->pid, task[next]->pid, task[next]->add_priority, task[next]->counter);
	if(current == task[next])
		return;
	switch_to(next);
}
#endif

inline void switch_to(int n) {
	struct task_struct *temp = current;

	current = task[n];
    rswitch_to(&(temp->tss), &(task[n]->tss));
}

//// 时钟中断C 函数处理程序，在kernel/system_call.s 中的_timer_interrupt（176 行）被调用。
// 参数cpl 是当前特权级0 或3，0 表示内核代码在执行。
// 对于一个进程由于执行时间片用完时，则进行任务切换。并执行一个计时更新工作。
void do_timer(long cpl)
{
  // 如果当前特权级(cpl)为0（最高，表示是内核程序在工作），则将超级用户运行时间stime 递增；
  // 如果cpl > 0，则表示是一般用户程序在工作，增加utime。
	if (cpl)
		current->utime++;
	else
		current->stime++;

#ifndef PREEMPTIVE
	if ((--current->counter) > 0)
		return;			// 如果进程运行时间还没完，则退出。
	current->counter = 0;
#else
	if(current->counter > 0)
		--current->counter;
	if(current->counter < 3 && current->pid == 4) {
		--current->add_priority;
		printf("\e[31m[PID = %d] Priority Update %d -> %d\e[0m\n", current->pid, current->add_priority + 1, current->add_priority);
	}
#endif
	if (!cpl)
		return;			// 对于超级用户程序，不依赖counter 值进行调度。
	schedule();
}

void idle() 
{
	printf("\e[33m[PID = %d] Please Prove Your Context Switch is Right in each Child Process\e[0m\n", current->pid);
	// sys_enableTimeInterrupt();
    while(1);
}

void sched_init() 
{
	for(int i = 1; i < NR_TASKS; i++)
		task[i] = NULL;
}
