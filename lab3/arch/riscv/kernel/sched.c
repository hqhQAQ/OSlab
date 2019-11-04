#include <sched.h>

union task_union {
	struct task_struct task;
	char stack[PAGE_SIZE];
};
static union task_union init_task = { INIT_TASK, };	
struct task_struct * current = &(init_task.task);
struct task_struct * task[NR_TASKS] = {&(init_task.task), };

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
	switch_to(next);
}

inline void switch_to(int n) {
    rswitch_to(&current->tss, &task[n]->tss);
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

	if ((--current->counter) > 0)
		return;			// 如果进程运行时间还没完，则退出。
	current->counter = 0;
	if (!cpl)
		return;			// 对于超级用户程序，不依赖counter 值进行调度。
	schedule();
}

void idle() 
{
    while(1);
}

void sched_init() 
{
	for(int i = 1; i < NR_TASKS; i++)
		task[i] = NULL;
}