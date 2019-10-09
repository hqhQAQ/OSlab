.section .text
.globl _start
.extern start_kernel
_start:
	li t0, 2048
	csrw mstatus, t0
	csrw mie, zero
	csrw mip, zero
	csrw mtvec, zero
	mret
	csrw stvec, zero
	mv sp, zero
	addi sp, sp, -100 # sp =sp1 -100m
	tail start_kernel
