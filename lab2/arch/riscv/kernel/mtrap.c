#include <stdio.h>
#include <csr.h>
#include <machine.h>

void mtrap_handler(unsigned long* regs, unsigned long mcause, unsigned long mepc) 
{
    
    // interrupt
    if((long)mcause < 0) {
        unsigned long *mtimecmp = (void *)0x2004000;
        unsigned long *mtime = (void *)0x200BFF8;
        *mtimecmp = *mtime + 10000000;
        write_csr_enum(csr_mip, set_field(read_csr_enum(csr_mip), 1 << IRQ_S_TIMER, 1));
    }
    // exception
    else {
        write_csr_enum(csr_mepc, read_csr_enum(csr_mepc) + 4);
        switch (mcause)
        {
        case 9:
            {
                unsigned long *mtimecmp = (void *)0x2004000;
                unsigned long *mtime = (void *)0x200BFF8;
                *mtimecmp = *mtime + 10000000;
                write_csr_enum(csr_mip, set_field(read_csr_enum(csr_mip), 1 << IRQ_S_TIMER, 0));
            }
            break;   
        default:
            break;
        }
    }
}
