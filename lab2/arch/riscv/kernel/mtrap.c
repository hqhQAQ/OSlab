#include <ns16550a.h>

// uint8_t *clint = (uint8_t *)(void *)SIFIVE_CLINT_CTRL_ADDR;
int count = 0;

void trap_handler() 
{
   ns16550a_init();
   ns16550a_putchar('0' + count++);
   ns16550a_putchar('\n');
   if(count > 9)
      count  = 0;
}
