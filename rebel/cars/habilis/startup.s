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
    .word SysTick_Handler   /* SysTick */

    .word Default_Handler   /* IRQ0 - WWDG */
    .word Default_Handler   /* IRQ1 - PVD */
    .word Default_Handler   /* IRQ2 - TAMPER */
    .word Default_Handler   /* IRQ3 - RTC */
    .word Default_Handler   /* IRQ4 - FLASH */
    .word Default_Handler   /* IRQ5 - RCC */
    .word Default_Handler   /* IRQ6 - EXTI0 */
    .word Default_Handler   /* IRQ7 - EXTI1 */
    .word Default_Handler   /* IRQ8 - EXTI2 */
    .word Default_Handler   /* IRQ9 - EXTI3 */
    .word Default_Handler   /* IRQ10 - EXTI4 */
    .word Default_Handler   /* IRQ11 - DMA1_Channel1 */
    .word Default_Handler   /* IRQ12 - DMA1_Channel2 */
    .word Default_Handler   /* IRQ13 - DMA1_Channel3 */

/* Reset Handler */
.section .text.Reset_Handler
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
/* Call the clock system initialization function.*/
    bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */
    ldr r0, =_sdata
    ldr r1, =_etext
    ldr r2, =_edata

1:  cmp r0, r2
    ittt lt
    ldrlt r3, [r1], #4
    strlt r3, [r0], #4
    blt 1b

    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
2:  cmp r0, r1
    it lt
    strlt r2, [r0], #4
    blt 2b

/* Call the application's entry point.*/
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
