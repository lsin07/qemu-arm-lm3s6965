/* LM3S6965 Register Definitions (Minimal) */
#define UART0_BASE      0x4000C000
#define UART0_DR        (*((volatile uint32_t *)(UART0_BASE + 0x000))) /* Data Register */
#define UART0_IM        (*((volatile uint32_t *)(UART0_BASE + 0x038))) /* Interrupt Mask */
#define UART0_MIS       (*((volatile uint32_t *)(UART0_BASE + 0x040))) /* Masked Interrupt Status */
#define UART0_ICR       (*((volatile uint32_t *)(UART0_BASE + 0x044))) /* Interrupt Clear */

/* NVIC Registers */
#define NVIC_EN0        (*((volatile uint32_t *)0xE000E100)) /* IRQ 0-31 Enable */
