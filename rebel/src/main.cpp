#include <stdint.h>

#include <car.h>

#define USART1_BASE   0x40013800

#define USART1_SR     (*(volatile uint32_t*)(USART1_BASE + 0x00)) // Status register
#define USART1_DR     (*(volatile uint32_t*)(USART1_BASE + 0x04)) // Data register
#define USART1_BRR    (*(volatile uint32_t*)(USART1_BASE + 0x08)) // Baud rate
#define USART1_CR1    (*(volatile uint32_t*)(USART1_BASE + 0x0C)) // Control register 1

#define USART_SR_TXE  (1 << 7)
#define USART_CR1_UE  (1 << 13)
#define USART_CR1_TE  (1 << 3)

static void usart1_init(void) {
    // Set baud rate to 9600 (assume 72 MHz clock)
    USART1_BRR = 0x1D4C;  // = 72000000 / 9600

    // Enable USART, Transmit enable
    USART1_CR1 = USART_CR1_UE | USART_CR1_TE;
}

static void usart1_send_char(char c) {
    while (!(USART1_SR & USART_SR_TXE));
    USART1_DR = c;
}

static void usart1_puts(const char* s) {
    while (*s) {
        usart1_send_char(*s++);
    }
}

int main() {
    usart1_init();
    usart1_puts("Hello from STM32F103!\r\n");

    while (1);
}
