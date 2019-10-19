#include <stdio.h>

// uint8_t *clint = (uint8_t *)(void *)SIFIVE_CLINT_CTRL_ADDR;
int count = 0;

void trap_handler() 
{
   printf("%d\n", count++);
}
