OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS
{
    .text : { *(.text*) } > ram
    .data : { *(.data*) } > ram
    .bss : { _bss = .; *(.bss*) . = ALIGN(4); _ebss = .; } > ram
}