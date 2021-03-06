.equ MAX_HARTS, 16
.equ SAVE_REGS, 32
.equ STACK_SIZE, 4096
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

.macro save_all stack
    sd      x2, (2 * REGBYTES)(\stack)
    mv      sp, \stack
    sxsp    x1, 1
    sxsp    x2, 2
    sxsp    x3, 3
    sxsp    x4, 4
    sxsp    x5, 5
    sxsp    x6, 6
    sxsp    x7, 7
    sxsp    x8, 8
    sxsp    x9, 9
    sxsp    x10, 10
    sxsp    x11, 11
    sxsp    x12, 12
    sxsp    x13, 13
    sxsp    x14, 14
    sxsp    x15, 15
    sxsp    x16, 16
    sxsp    x17, 17
    sxsp    x18, 18
    sxsp    x19, 19
    sxsp    x20, 20
    sxsp    x21, 21
    sxsp    x22, 22
    sxsp    x23, 23
    sxsp    x24, 24
    sxsp    x25, 25
    sxsp    x26, 26
    sxsp    x27, 27
    sxsp    x28, 28
    sxsp    x29, 29
    sxsp    x30, 30
    sxsp    x31, 31
    ld      x2, (2 * REGBYTES)(\stack)
.endm

.macro load_all stack
    mv      sp, \stack
    lxsp    x1, 1
    lxsp    x3, 3
    lxsp    x4, 4
    lxsp    x5, 5
    lxsp    x6, 6
    lxsp    x7, 7
    lxsp    x8, 8
    lxsp    x9, 9
    lxsp    x10, 10
    lxsp    x11, 11
    lxsp    x12, 12
    lxsp    x13, 13
    lxsp    x14, 14
    lxsp    x15, 15
    lxsp    x16, 16
    lxsp    x17, 17
    lxsp    x18, 18
    lxsp    x19, 19
    lxsp    x20, 20
    lxsp    x21, 21
    lxsp    x22, 22
    lxsp    x23, 23
    lxsp    x24, 24
    lxsp    x25, 25
    lxsp    x26, 26
    lxsp    x27, 27
    lxsp    x28, 28
    lxsp    x29, 29
    lxsp    x30, 30
    lxsp    x31, 31
    lxsp    x2, 2
.endm
