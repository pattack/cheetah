.syntax unified
.cpu cortex-m3
.thumb

/* Vector Table (placed at 0x00000000 by linker) */
.section .isr_vector, "a", %progbits
.type isr_vector, %object
.size isr_vector, .-isr_vector

isr_vector:
    .word _stack_top        /* Initial Stack Pointer */
    .word Reset_Handler     /* Reset vector */
    .word Default_Handler   /* NMI */
    .word Default_Handler   /* HardFault */
    .word Default_Handler   /* MemManage */
    .word Default_Handler   /* BusFault */
    .word Default_Handler   /* UsageFault */
    .word 0                 /* Reserved */
    .word 0
    .word 0
    .word 0
    .word Default_Handler   /* SVCall */
    .word Default_Handler   /* DebugMonitor */
    .word 0                 /* Reserved */
    .word Default_Handler   /* PendSV */
    .word Default_Handler   /* SysTick */

/* Reset Handler */
.section .text.Reset_Handler
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    bl main         /* Call main() */
1:  b 1b            /* Infinite loop after main returns */

/* Default interrupt handler */
.section .text.Default_Handler
.global Default_Handler
.type Default_Handler, %function

Default_Handler:
1:  b 1b

/* Stack top (placed in .stack section by linker) */
.section .stack, "a", %progbits
.word 0x20010000     /* Example top of RAM (adjust based on your MCU's RAM size) */
.global _stack_top
_stack_top:
