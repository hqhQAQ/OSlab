#include <ns16550a.h>

void trap_handler() 
{
    ns16550a_putchar('h');
}