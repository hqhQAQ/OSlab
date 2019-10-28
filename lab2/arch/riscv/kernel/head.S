.include "macro.S"

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
    # close other harts
    csrr a0, mhartid
    bnez a0, park
    # set up stack
    slli t3, t3, STACK_SHIFT
    la sp, stacks + STACK_SIZE
    add sp, sp, t3    
    # init .bss
    la a3, _bss_start
    la a4, _bss_end
    ble a4, a3, clear_bss_done
clear_bss:
    sd zero, 0(a3)
    add a3, a3, REGBYTES
    blt a3, a4, clear_bss
clear_bss_done:
    # disable mie / mip
    csrw mie, zero
    csrw mip, zero
    # set mtvec
    la t0, mtrap_vector
    csrw mtvec, t0
    # init ns16550a
    jal ra, ns16550a_init
    # set stvec
    la t0, strap_vector
    csrw stvec, t0
    # set midelege and mstatus
    call initCSR
    csrr t0, sstatus
    csrr t1, sie
    ecall
    tail start_kernel

park:
    wfi
    j park

    .align 4
mtrap_vector:
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
    mv      a0, sp
    csrr    a1, mcause
    csrr    a2, mepc    
    jal ra, mtrap_handler
    
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

    .bss
    .align 4
    .global stacks
stacks:
    .skip STACK_SIZE * MAX_HARTS
