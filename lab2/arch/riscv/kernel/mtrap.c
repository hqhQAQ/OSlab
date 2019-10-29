#include <stdio.h>
#include <csr.h>
#include <machine.h>

void mtrap_handler(unsigned long* regs, unsigned long mcause, unsigned long mepc) 
{
    
    // interrupt
    if((long)mcause < 0) {
        mcause &= 0x7FFFFFFFFFFFFFFF;
        switch (mcause)
        {
        case IRQ_M_TIMER:
            // close m time interrupt
            write_csr_enum(csr_mie, set_field(read_csr_enum(csr_mie), 1 << IRQ_M_TIMER, 0));  
            // start s time interrupt
            write_csr_enum(csr_mip, set_field(read_csr_enum(csr_mip), 1 << IRQ_S_TIMER, 1));
            /* code */
            break;
        default:
            break;
        }
    }
    // exception
    else {
        // ip = ip + 4
        write_csr_enum(csr_mepc, read_csr_enum(csr_mepc) + 4);
        switch (mcause)
        {
        // s mode software exception
        case 9:
            {
                unsigned long *mtimecmp = (void *)0x2004000;
                unsigned long *mtime = (void *)0x200BFF8;
                *mtimecmp = *mtime + 10000000;
                // close s time interrupt
                write_csr_enum(csr_mip, set_field(read_csr_enum(csr_mip), 1 << IRQ_S_TIMER, 0));
                // open m time interrupt
                write_csr_enum(csr_mie, set_field(read_csr_enum(csr_mie), 1 << IRQ_M_TIMER, 1));  
                
            }
            break;   
        default:
            break;
        }
    }
}
