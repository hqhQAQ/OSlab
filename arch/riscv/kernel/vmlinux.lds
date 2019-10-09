OUTPUT_ARCH(riscv)
ENTRY(_start)
SECTIONS
{
    . = 0xffffffe000000000;
    _start = .;
    .text : {*(.text)}
    .data : {*(.data)}
    .bss : {*(.bss)}
    
}