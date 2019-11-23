OUTPUT_ARCH( "riscv" )

ENTRY( _start )

SECTIONS
{
  . = 0x2000;
  PROVIDE(START_VA = .);
  BASE_ADDR = 0X80000000;
  .text 0x2000 : AT (BASE_ADDR) {
    PROVIDE(_text_start = .);
    *(.text.init) *(.text .text.*)
    PROVIDE(_text_end = .);
  }

  .rodata 0x6000 : AT (BASE_ADDR + 0X4000) {
    PROVIDE(_rodata_start = .);
    *(.rodata .rodata.*)
    PROVIDE(_rodata_end = .);
  }

  .data 0xa000 : AT (BASE_ADDR + 0x8000) {
    PROVIDE(_data_start = .);
    *(.sdata .sdata.*) *(.data .data.*)
    PROVIDE(_data_end = .);
  }

  .bss 0xe000 : AT (BASE_ADDR + 0xc000) {
    PROVIDE(_bss_start = .);
    *(.sbss .sbss.*) *(.bss .bss.*)
    PROVIDE(_bss_end = .);
  }

}


