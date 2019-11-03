.equ MAX_HARTS, 4
.equ SAVE_REGS, 16
.equ STACK_SIZE, 1024
.equ STACK_SHIFT, 10
.equ REGBYTES, 8
.equ CONTEXT_SIZE, (SAVE_REGS * REGBYTES)
.equ CLINT_BASE, 0x2000000
.equ MTIMECMP_OFFSET, 0x4000
.equ MTIME, 0xBFF8

# save register to stack
.macro lxsp a, b
ld \a, ((\b)*REGBYTES)(sp)
.endm

.macro sxsp a, b
sd \a, ((\b)*REGBYTES)(sp)
.endm
