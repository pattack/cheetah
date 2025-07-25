/* Linker script for STM32F103C8T6 */

ENTRY(Reset_Handler)

/* 64KB FLASH, 20KB RAM */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
  RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
  /* Interrupt Vector Table and code */
  .isr_vector :
  {
    KEEP(*(.isr_vector)) /* Vector table kept in output */
  } > FLASH

  .text :
  {
    *(.text*)           /* Program code */
    *(.rodata*)         /* Read-only data */
    _etext = .;         /* End of .text section */
  } > FLASH

  /* Initialized data copied from FLASH to RAM at startup */
  .data : AT (ADDR(.text) + SIZEOF(.text))
  {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM

  /* Uninitialized data - zero-initialized by startup code */
  .bss :
  {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > RAM

  /* Heap section for malloc */
  .heap (COPY) :
  {
    _sheap = .;
    . = . + 4K; /* Define 4KB heap size, adjust as needed */
    _eheap = .;
  } > RAM

  /* Stack section */
  .stack (COPY) :
  {
    _sstack = .;
    . = . + 2K; /* Define 2KB stack size, adjust as needed */
    _estack = .;
  } > RAM

  /* End of RAM marker */
  end = .;
}

/* Define symbols for startup assembly */
PROVIDE(_stack_top = ORIGIN(RAM) + LENGTH(RAM));
