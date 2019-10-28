#include <csr.h>
#include <machine.h>

void initCSR() 
{
    // set mideleg.stimer = 1
    set_field(read_csr_enum(csr_mideleg), IRQ_S_TIMER, 1);
    set_field(read_csr_enum(csr_mstatus), MSTATUS_MPP, 1);
    set_field(read_csr_enum(csr_mstatus), MSTATUS_MPIE, 1);
    set_field(read_csr_enum(csr_mstatus), MSTATUS_MIE, 1);
    set_field(read_csr_enum(csr_mie), IRQ_M_TIMER, 1);
    set_field(read_csr_enum(csr_sstatus), MSTATUS_MIE, 1);
    set_field(read_csr_enum(csr_sie), IRQ_S_TIMER, 1);
    mode_set_and_continue(0x01);
}