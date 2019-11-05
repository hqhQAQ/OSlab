#ifndef SCHED_H
#define SCHED_H

#include <stddef.h>

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

#define NR_TASKS 16
#define PAGE_SIZE 4096
#define STACK 0x80003560

enum PROC_STATE{
    TASK_RUNNING,
    TASK_INTERRUPTIBLE,
    TASK_UNINTERRUPTIBLE,
    TASK_ZOMBIE,
    TASK_STOPPED
};

struct tss_struct {
    uint64_t pc;
    uint64_t ra;	//return address
	uint64_t sp;
	uint64_t gp;	//global pointer
	uint64_t tp;	//thread pointer
	uint64_t t0;	//..
	uint64_t t1;
	uint64_t t2;	//temporary
	uint64_t fp;	//(s0)frame pointer
	uint64_t s1;
	uint64_t a0;	//..
	uint64_t a1;	//para/return value
	uint64_t a2;	//..
	uint64_t a3;
	uint64_t a4;
	uint64_t a5;
	uint64_t a6;
	uint64_t a7;	//para
	uint64_t s2;	//..
	uint64_t s3;
	uint64_t s4;
	uint64_t s5;
	uint64_t s6;
	uint64_t s7;
	uint64_t s8;
	uint64_t s9;
	uint64_t s10;
	uint64_t s11;	//saved registers
	uint64_t t3;	//..
	uint64_t t4;
	uint64_t t5;
	uint64_t t6;	//temporary paras
};

struct task_struct {
/* these are hardcoded - don't touch */
	long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
	long counter;
	long priority;
	long pid;
	long utime, stime;
/* tss for this task */
	struct tss_struct tss;
};

/*
 *  INIT_TASK is used to set up the first task table, touch at
 * your own risk!. Base=0, limit=0x9ffff (=640kB)
 */
#define INIT_TASK \
/* state etc */	{ 0,15,15, 0, 0, 0,\
/* todo tss */    {(uint64_t)idle, 0, (uint64_t)STACK, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0, \
				  0, 0, 0, 0, 0, 0, 0, 0 \
				  } \
                }

extern struct task_struct * current;
extern struct task_struct * task[NR_TASKS];

extern void rswitch_to(struct tss_struct *from, struct tss_struct *to);
void switch_to(int n);
void idle();
void do_timer(long cpl);
void schedule();

#endif