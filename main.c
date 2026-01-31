#include <stdio.h>
#include <stdint.h>

/* * Function prototype for semihosting initialization.
 * This is required when using rdimon.specs with newlib.
 */
extern void initialise_monitor_handles(void);

int main(void) {
    /* Initialize semihosting capabilities */
    initialise_monitor_handles();

    /* Test print using semihosting */
    printf("Hello, QEMU LM3S6965!\n");

    /* * User code area:
     * Write your application logic here.
     */
    volatile uint64_t counter = 0;

    while (1) {
        /* Infinite loop to keep the simulation running */
        counter++;
    }

    return 0;
}
