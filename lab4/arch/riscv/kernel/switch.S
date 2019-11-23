.include "macro.S"

.text
.globl rswitch_to
rswitch_to:
    csrr    sp, sscratch 
    addi    sp, sp, -CONTEXT_SIZE
	# store a0, a1
	addi	sp, sp, -16
	sxsp	a0, 0
	sxsp	a1, 1
	# set pc
	csrr	t0, sepc
	sd		t0, 0(a0)
	# Restore registers.
	addi	sp, sp, 16
	load_all sp
	# sp = old a0
	addi	sp, sp, -16
	lxsp	sp, 0
	save_all sp
    csrr    t0, sscratch # t0 = old sp
	sxsp	t0, 2 # save old sp
	
	mv		a7, zero
	ecall
	# get old a1
	mv		sp, t0
	addi    sp, sp, -CONTEXT_SIZE
	addi	sp, sp, -16
	lxsp	sp, 1
	# load pc
	lxsp	t1, 0
	csrw	sepc, t1
	# load all
	load_all sp
	sret
