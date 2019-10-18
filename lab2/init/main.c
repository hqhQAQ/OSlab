#include <ns16550a.h>

void start_kernel()
{
    char str[20] = "Hello RISC-V! "; 
    
    ns16550a_init();
    for (int i = 0; str[i] != '\0'; i++)
    {
        ns16550a_putchar(str[i]);
    }
}
