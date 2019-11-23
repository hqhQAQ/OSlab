#ifndef SYSCALL_H
#define SYSCALL_H

// 0号中断, 完成s mode时钟中断(收尾工作)
void sys_overTimeInterrupt();
// 1号中断,关闭时钟中断
void sys_disableTimeInterrupt();
// 2号中断,打开时钟中断
void sys_enableTimeInterrupt();

#endif