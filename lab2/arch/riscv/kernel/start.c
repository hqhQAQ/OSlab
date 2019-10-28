#include <csr.h>
#include <machine.h>

void initCSR() 
{
    unsigned long *mtimecmp = (void *)0x2004000;
    *mtimecmp = 100000;
    // set mideleg.stimer = 1
    write_csr_enum(csr_mideleg, set_field(read_csr_enum(csr_mideleg), 1 << IRQ_S_TIMER, 1));
    write_csr_enum(csr_mstatus, set_field(read_csr_enum(csr_mstatus), MSTATUS_MPP, 1));
    write_csr_enum(csr_mstatus, set_field(read_csr_enum(csr_mstatus), MSTATUS_MPIE, 1));
    write_csr_enum(csr_mstatus, set_field(read_csr_enum(csr_mstatus), MSTATUS_SIE, 1));
    write_csr_enum(csr_mie, set_field(read_csr_enum(csr_mie), 1 << IRQ_S_TIMER, 1)); 
    write_csr_enum(csr_mie, set_field(read_csr_enum(csr_mie), 1 << IRQ_M_TIMER, 1));    
    write_csr_enum(csr_sstatus, set_field(read_csr_enum(csr_sstatus), SSTATUS_SIE, 1));
    write_csr_enum(csr_sie, set_field(read_csr_enum(csr_sie), 1 << IRQ_S_TIMER, 1));
    {
        asm volatile ("csrr t0, mstatus");
        asm volatile ("csrr t1, sstatus");
        asm volatile ("csrr t2, sie");
    }
    write_csr_enum(csr_mstatus, set_field(read_csr_enum(csr_mstatus), MSTATUS_MIE, 1));
    mode_set_and_continue(PRV_S);
}