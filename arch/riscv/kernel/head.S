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
    # set up stack
    csrr t0, mhartid
    slli t0, t0, STACK_SHIFT
    la sp, stacks + STACK_SIZE
    add sp, sp, t0

    # park all harts except 0
    csrr a0, mhartid
    bnez a0, park

    tail start_kernel

park:
    wfi
    j park

    .bss
    .align 4
    .global stacks
stacks:
    .skip STACK_SIZE * MAX_HARTS
