.include "macro.S"

.globl _text_start
.globl _text_end
.globl _rodata_start
.globl _rodata_end
.globl _data_start
.globl _data_end
.globl _bss_start
.globl _bss_end
# .global _memory_start;
# .global _memory_end;

.section .text.init, "ax", @progbits
.global _start

_start:
    # close other harts
    csrr a0, mhartid
    bnez a0, park
    # set up stack
    la sp, stacks + STACK_SIZE * 3   
    # init .bss
    la a3, _bss_start
    la a4, _bss_end
    ble a4, a3, clear_bss_done
clear_bss:
    sd zero, 0(a3)
    add a3, a3, REGBYTES
    blt a3, a4, clear_bss
clear_bss_done:
    csrw satp, x0
    # set mtvec
    la t0, mtrap_vector
    csrw mtvec, t0    
    # set csr and switch to s mode
    call initCSR
	call total_mapping
	call enter_s_mode
	call init_sstatus
    call init_satp
	# jump to low address
	la t0, after_virtual
	andi t1, t0, 255
	addi t0, x0, 1
	slli t0, t0, 13
	add t1, t1, t0	
	mv ra, t1
	jr ra

after_virtual:
	# set stvec
    la t0, strap_vector
    csrw stvec, t0
	# init ns16550a
	jal ra, ns16550a_init

    la sp, stacks + STACK_SIZE * 4
    # call test_rwx
	tail start_kernel

park:
    wfi
    j park

    .align 4
mtrap_vector:
    # Save registers.
    csrw    mscratch, sp
    la      sp, stacks + STACK_SIZE * 3
    addi    sp, sp, -CONTEXT_SIZE
    save_all sp

    # Invoke the handler.
    mv      a0, sp
    csrr    a1, mcause
    csrr    a2, mepc    
    jal ra, mtrap_handler
    
    # Restore registers.
    load_all sp
    csrr    sp, mscratch  
    # Return
    mret

    .bss
    .align 4
    .global stacks
stacks:
    .skip STACK_SIZE * MAX_HARTS
