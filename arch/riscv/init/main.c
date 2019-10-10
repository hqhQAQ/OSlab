enum {
    HART0_CLOCK_FREQ           = 0x00010000,
    UART0_CLOCK_FREQ           = 0x00011000,
    UART0_BAUD_RATE            = 0x00011100,
    NS16550A_UART0_CTRL_ADDR   = 0x00030000,
    RISCV_HTIF_BASE_ADDR       = 0x00050000,
    SIFIVE_CLINT_CTRL_ADDR     = 0x55550000,
    SIFIVE_CLIC_CRTL_ADDR      = 0x55550001,
    SIFIVE_TEST_CTRL_ADDR      = 0x55550002,
    SIFIVE_UART0_CTRL_ADDR     = 0x55550010,
    SIFIVE_GPIO0_CTRL_ADDR     = 0x55550020,
    SIFIVE_SPI0_CTRL_ADDR      = 0x55550030,
};

enum {
    UART_RBR      = 0x00,  /* Receive Buffer Register */
    UART_THR      = 0x00,  /* Transmit Hold Register */
    UART_IER      = 0x01,  /* Interrupt Enable Register */
    UART_DLL      = 0x00,  /* Divisor LSB (LCR_DLAB) */
    UART_DLM      = 0x01,  /* Divisor MSB (LCR_DLAB) */
    UART_FCR      = 0x02,  /* FIFO Control Register */
    UART_LCR      = 0x03,  /* Line Control Register */
    UART_MCR      = 0x04,  /* Modem Control Register */
    UART_LSR      = 0x05,  /* Line Status Register */
    UART_MSR      = 0x06,  /* Modem Status Register */
    UART_SCR      = 0x07,  /* Scratch Register */

    UART_LCR_DLAB = 0x80,  /* Divisor Latch Bit */
    UART_LCR_8BIT = 0x03,  /* 8-bit */
    UART_LCR_PODD = 0x08,  /* Parity Odd */

    UART_LSR_DA   = 0x01,  /* Data Available */
    UART_LSR_OE   = 0x02,  /* Overrun Error */
    UART_LSR_PE   = 0x04,  /* Parity Error */
    UART_LSR_FE   = 0x08,  /* Framing Error */
    UART_LSR_BI   = 0x10,  /* Break indicator */
    UART_LSR_RE   = 0x20,  /* THR is empty */
    UART_LSR_RI   = 0x40,  /* THR is empty and line is idle */
    UART_LSR_EF   = 0x80,  /* Erroneous data in FIFO */
};

typedef struct auxval {
    unsigned long key;
    unsigned long val;
} auxval_t;

auxval_t __auxv[] = {
    { UART0_CLOCK_FREQ,         1843200    },
    { UART0_BAUD_RATE,          115200     },
    { NS16550A_UART0_CTRL_ADDR, 0x10000000 },
    { SIFIVE_TEST_CTRL_ADDR,    0x100000   },
    { 0, 0 }
};

unsigned long getauxval(unsigned long key)
{
    auxval_t *auxv = __auxv;
    while(auxv->key) {
        if (auxv->key == key) {
            return auxv->val;
        }
        auxv++;
    }
    return 0;
}

typedef struct console_device {
    void (*init)();
    int (*getchar)();
    int (*putchar)(int);
} console_device_t;

typedef __UINT8_TYPE__ uint8_t;
typedef __UINT32_TYPE__ uint32_t;
static volatile uint8_t *uart;

static void ns16550a_init()
{
	uart = (uint8_t *)(void *)getauxval(NS16550A_UART0_CTRL_ADDR);
	uint32_t uart_freq = getauxval(UART0_CLOCK_FREQ);
	uint32_t baud_rate = getauxval(UART0_BAUD_RATE);
    uint32_t divisor = uart_freq / (16 * baud_rate);
    uart[UART_LCR] = UART_LCR_DLAB;
    uart[UART_DLL] = divisor & 0xff;
    uart[UART_DLM] = (divisor >> 8) & 0xff;
    uart[UART_LCR] = UART_LCR_PODD | UART_LCR_8BIT;
}

static int ns16550a_getchar()
{
    if (uart[UART_LSR] & UART_LSR_DA) {
        return uart[UART_RBR];
    } else {
        return -1;
    }
}

static int ns16550a_putchar(int ch)
{
    while ((uart[UART_LSR] & UART_LSR_RI) == 0);
    return uart[UART_THR] = ch & 0xff;
}

void start_kernel()
{
    ns16550a_init();
    ns16550a_putchar('H');
    ns16550a_putchar('e');
    ns16550a_putchar('l');
    ns16550a_putchar('l');
    ns16550a_putchar('o');
    ns16550a_putchar(' ');
    ns16550a_putchar('W');
    ns16550a_putchar('o');
    ns16550a_putchar('r');
    ns16550a_putchar('l');
    ns16550a_putchar('d');
    ns16550a_putchar('!');
    ns16550a_putchar('\n');
}
