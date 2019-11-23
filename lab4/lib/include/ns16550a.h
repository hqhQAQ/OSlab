#ifndef NS16550A_H
#define NS16550A_H

typedef __UINT8_TYPE__ uint8_t;
typedef __UINT32_TYPE__ uint32_t;

enum {
    HART0_CLOCK_FREQ           = 0x00010000,
    UART0_CLOCK_FREQ           = 0x001C2000,
    UART0_BAUD_RATE            = 0x0001C200,
    NS16550A_UART0_CTRL_ADDR   = 0x10000000,
    RISCV_HTIF_BASE_ADDR       = 0x00050000,
    SIFIVE_CLINT_CTRL_ADDR     = 0x02000000,
    SIFIVE_CLIC_CRTL_ADDR      = 0x55550001,
    SIFIVE_TEST_CTRL_ADDR      = 0x00100000,
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

extern volatile uint8_t *uart;
int ns16550a_putchar(int ch);
void ns16550a_init();
int ns16550a_getchar();

#endif
