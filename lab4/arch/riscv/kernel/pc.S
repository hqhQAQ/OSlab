.globl get_pc
	.align 4
get_pc:
	addi sp, sp, -8
	sd t2, 0(sp)
	auipc t2, 0
	mv a0, t2
	ld t2, 0(sp)
	addi sp, sp, 8
	jr ra
