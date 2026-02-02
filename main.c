#include <stdio.h>
#include <stdint.h>
#include "lm3s6965_minimal.h"

/* * Function prototype for semihosting initialization.
 * This is required when using rdimon.specs with newlib.
 */
extern void initialise_monitor_handles(void);

void UART0_Handler(void) {
    /* Check if it is a Receive Interrupt (RX) */
    if (UART0_MIS & (1 << 4)) { 
        char c = (char)UART0_DR; /* Read clears the FIFO/Interrupt in some HW, but explicit clear is safer */

        UART0_ICR = (1 << 4); /* Clear RX Interrupt Flag */

        /* Interrupt Action Here */
        (void)c;
    }
}

int main(void) {
    /* Initialize semihosting capabilities */
    initialise_monitor_handles();

    /* Test print using semihosting */
    printf("Hello, QEMU LM3S6965!\n");

    /* 1. Unmask UART0 Receive Interrupt (RXIM bit 4) */
    UART0_IM |= (1 << 4);

    /* 2. Enable UART0 Interrupt in NVIC */
    /* UART0 is IRQ #5. So we set bit 5 of NVIC_EN0 */
    NVIC_EN0 = (1 << 5);

    volatile uint64_t counter = 0;
    
    /* * User code area:
    * Write your application logic here.
    *
    */

    while (1) {
        /* Infinite loop to keep the simulation running */
        counter++;
    }

    return 0;
}
