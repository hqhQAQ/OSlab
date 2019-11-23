#include <syscall.h>

// 0号中断, 完成s mode时钟中断(收尾工作)
void sys_overTimeInterrupt()
{
    asm volatile ("addi sp, sp, -24"); 
    asm volatile ("sd a7, 0(sp)"); 
    asm volatile ("sd s0, 8(sp)"); 
    asm volatile ("sd ra, 16(sp)"); 
    asm volatile ("mv a7, zero"); 
    asm volatile ("ecall"); 
    asm volatile ("ld a7, 0(sp)"); 
    asm volatile ("ld s0, 8(sp)");
    asm volatile ("ld ra, 16(sp)"); 
    asm volatile ("addi sp, sp, 24");
}
// 1号中断,关闭时钟中断
void sys_disableTimeInterrupt()
{
    asm volatile ("addi sp, sp, -24"); 
    asm volatile ("sd a7, 0(sp)"); 
    asm volatile ("sd s0, 8(sp)"); 
    asm volatile ("sd ra, 16(sp)"); 
    asm volatile ("addi a7, zero, 1"); 
    asm volatile ("ecall"); 
    asm volatile ("ld a7, 0(sp)"); 
    asm volatile ("ld s0, 8(sp)");
    asm volatile ("ld ra, 16(sp)"); 
    asm volatile ("addi sp, sp, 24");
}
// 2号中断,打开时钟中断
void sys_enableTimeInterrupt()
{
    asm volatile ("addi sp, sp, -24"); 
    asm volatile ("sd a7, 0(sp)"); 
    asm volatile ("sd s0, 8(sp)"); 
    asm volatile ("sd ra, 16(sp)"); 
    asm volatile ("addi a7, zero, 2"); 
    asm volatile ("ecall"); 
    asm volatile ("ld a7, 0(sp)"); 
    asm volatile ("ld s0, 8(sp)");
    asm volatile ("ld ra, 16(sp)"); 
    asm volatile ("addi sp, sp, 24");
}
