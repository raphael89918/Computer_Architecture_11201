/* Linker script for RISC-V */

OUTPUT_ARCH("riscv:rv32i")

ENTRY(main)

/* Specify the memory layout for the target architecture */
MEMORY {
  ram : ORIGIN = 0x00000000, LENGTH = 64K  /* 根据需要调整内存大小 */
}

/* Define sections */
SECTIONS {
  . = 0x00000000;  /* 将初始位置计数器设置为 RAM 的开始位置 */

  /* .text 段用于代码 */
  .text : {
    *(.text)   /* 来自输入文件的 .text 段的代码 */
  }

  /* .data 段用于初始化数据 */
  .data : {
    *(.data)   /* 来自输入文件的 .data 段的初始化数据 */
  }

  /* .bss 段用于未初始化数据 */
  .bss : {
    *(.bss)    /* 来自输入文件的 .bss 段的未初始化数据 */
  }

  /* 将 .bss 段的结束对齐到 4 字节边界 */
  . = ALIGN(4);
}
