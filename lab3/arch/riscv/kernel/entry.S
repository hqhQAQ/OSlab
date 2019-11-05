.include "macro.S"
.globl strap_vector
    .align 4
strap_vector:
    # Save registers.
    csrw    sscratch, sp
    addi    sp, sp, -CONTEXT_SIZE
    save_all sp

    # Invoke the handler.
    mv      a0, sp
    csrr    a1, scause
    csrr    a2, sepc    
    jal     ra, strap_handler
    
    # Restore registers.
    load_all sp
    csrr    sp, sscratch  
    # Return
    sret
