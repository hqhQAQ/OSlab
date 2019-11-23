.equ MAX_HARTS, 4
.equ SAVE_REGS, 16
.equ STACK_SIZE, 1024
.equ STACK_SHIFT, 10
.equ REGBYTES, 8
.equ CONTEXT_SIZE, (SAVE_REGS * REGBYTES)

.globl _text_start
.globl _text_end
.globl _rodata_start
.globl _rodata_end
.globl _data_start
.globl _data_end
.globl _bss_start
.globl _bss_end
.global _memory_start;
.global _memory_end;

.section .text.init, "ax", @progbits
.global _start

_start:
    # close mie and mip
    csrw mie, zero
    csrw mip, zero
    # set mtvec
    la t0, trap_handler
    csrw mtvec, t0

    csrr t0, mstatus
    # set mstatus.mie = 0
    addi t1, zero, -7
    # t0 = t0 & 0xfffffffffffffff7
    and t0, t0, t1

    # set mstatus.mpp = 01 to super mode
    addi t1, zero, 1
    # t1 = 0x0000_0000_0000_0400
    slli t1, t1, 11
    or t0, t0, t1    

    # set mstatus.mpie = 0
    addi t1, zero, 128
    addi t2, t2, -1
    xor t1, t1, t2
    and t0, t0, t1
    csrw  mstatus, t0

    # switch to super mode
    la t0, Super
    csrw mepc, t0
    mret
Super:
    # set stvec
    # set mtvec
    la t0, trap_handler
    csrw stvec, t0
    # set up stack
    slli t3, t3, STACK_SHIFT
    la sp, stacks + STACK_SIZE
    add sp, sp, t3

    tail start_kernel


    .bss
    .align 4
    .global stacks
stacks:
    .skip STACK_SIZE * MAX_HARTS

    .align 2
trap_handler:
    mret
