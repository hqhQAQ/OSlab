#include <stdio.h>
#include <machine.h>

void strap_handler(unsigned long* regs, unsigned long mcause, unsigned long mepc) 
{
    static unsigned long count = 0;
    // interrupt
    if((long)mcause < 0) {
        mcause &= 0x7FFFFFFFFFFFFFFF;
        switch (mcause)
        {
        case IRQ_S_TIMER:
            printf("[S] Supervisor Mode Timer Interrupt %d\n", count++);
            {
                asm volatile ("ecall");
            }
            /* code */
            break;
        default:
            break;
        }
    }
    // exception
    else {
        switch (mcause)
        {
        default:
            break;
        }
    }
}