.equ MAX_HARTS, 4
.equ SAVE_REGS, 16
.equ STACK_SIZE, 1024
.equ STACK_SHIFT, 10
.equ REGBYTES, 8
.equ CONTEXT_SIZE, (SAVE_REGS * REGBYTES)

# save register to stack
.macro lxsp a, b
ld \a, ((\b)*REGBYTES)(sp)
.endm

.macro sxsp a, b
sd \a, ((\b)*REGBYTES)(sp)
.endm

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
    slli t3, t3, STACK_SHIFT
    la sp, stacks + STACK_SIZE
    add sp, sp, t3
    # init .bss

    # set mideleg

    # set mtimecmp

    # set [m|s]status, [m|s]ie

    # 打开机器模式下的时钟中断
    li t0, 7
    csrw mie, t0
    csrw mip, t0
    # set mtvec
    la t0, trap_vector
    csrw mtvec, t0

    csrr t0, mstatus
    # set mstatus.mie = 1
    addi t1, zero, 8
    # t0 = t0 | 0x0000000000000008
    or t0, t0, t1

    # set mstatus.mpp = 01 to super mode
    # addi t1, zero, 1
    # t1 = 0x0000_0000_0000_0400
    # slli t1, t1, 11
    # or t0, t0, t1    

    # set mstatus.mpie = 0
    # addi t1, zero, 128
    # addi t2, t2, -1
    # xor t1, t1, t2
    # and t0, t0, t1
    csrw  mstatus, t0

    # switch to super mode
#     la t0, Super
#     csrw mepc, t0
#     mret
# Super:
#     # set stvec
#     # set mtvec
#     la t0, trap_vector
#     csrw stvec, t0

    tail start_kernel


    .bss
    .align 4
    .global stacks
stacks:
    .skip STACK_SIZE * MAX_HARTS

    .align 2
trap_vector:
    # Save registers.
    addi    sp, sp, -CONTEXT_SIZE
    sxsp    ra, 0
    sxsp    a0, 1
    sxsp    a1, 2
    sxsp    a2, 3
    sxsp    a3, 4
    sxsp    a4, 5
    sxsp    a5, 6
    sxsp    a6, 7
    sxsp    a7, 8
    sxsp    t0, 9
    sxsp    t1, 10
    sxsp    t2, 11
    sxsp    t3, 12
    sxsp    t4, 13
    sxsp    t5, 14
    sxsp    t6, 15

    # Invoke the handler.
    csrr    a1, mcause
#    bgez    a1, exception
    jal     trap_handler
exception:

    # Restore registers.
    lxsp    ra, 0
    lxsp    a0, 1
    lxsp    a1, 2
    lxsp    a2, 3
    lxsp    a3, 4
    lxsp    a4, 5
    lxsp    a5, 6
    lxsp    a6, 7
    lxsp    a7, 8
    lxsp    t0, 9
    lxsp    t1, 10
    lxsp    t2, 11
    lxsp    t3, 12
    lxsp    t4, 13
    lxsp    t5, 14
    lxsp    t6, 15
    addi sp, sp, CONTEXT_SIZE

    # Return
    mret
