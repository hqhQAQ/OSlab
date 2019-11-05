#include <stdio.h>
#include <csr.h>
#include <machine.h>

void mtrap_handler(unsigned long* regs, unsigned long mcause, unsigned long mepc) 
{
    // printf("mtrap\n");
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
        // printf("exceptopn\n");
        // ip = ip + 4
        write_csr_enum(csr_mepc, mepc + 4);
        switch (mcause)
        {
        // s mode software exception
        case 9:
            if(regs[17] == 0) {
                // printf("s software exception\n");
                unsigned long *mtimecmp = (void *)0x2004000;
                unsigned long *mtime = (void *)0x200BFF8;
                *mtimecmp = *mtime + 500000;
                // close s time interrupt
                write_csr_enum(csr_mip, set_field(read_csr_enum(csr_mip), 1 << IRQ_S_TIMER, 0));
                // open m time interrupt
                write_csr_enum(csr_mie, set_field(read_csr_enum(csr_mie), 1 << IRQ_M_TIMER, 1));  
            }
            else if(regs[17] == 1) {
                // close m time interrupt
                write_csr_enum(csr_mie, set_field(read_csr_enum(csr_mie), 1 << IRQ_M_TIMER, 0));  
            }
            else if(regs[17] == 2) {
                // open m time interrupt
                write_csr_enum(csr_mie, set_field(read_csr_enum(csr_mie), 1 << IRQ_M_TIMER, 1));  
            }
            break;   
        default:
            break;
        }
    }
}
