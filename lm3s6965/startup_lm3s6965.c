#include <stdint.h>

/* Defined in linker script */
extern uint32_t _estack;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sidata;

/* Main function prototype */
extern int main(void);

/* Reset Handler */
void Reset_Handler(void) {
    uint32_t *pSrc, *pDest;

    /* Copy the data segment initializers from flash to SRAM */
    pSrc = &_sidata;
    for (pDest = &_sdata; pDest < &_edata;) {
        *pDest++ = *pSrc++;
    }

    /* Zero fill the bss segment */
    for (pDest = &_sbss; pDest < &_ebss;) {
        *pDest++ = 0;
    }

    /* Call the application's entry point */
    main();

    /* Should not reach here */
    while (1);
}

/* Default Handler for unexpected interrupts */
void Default_Handler(void) {
    while (1);
}

/* Vector Table */
__attribute__((section(".isr_vector")))
void (*const g_pfnVectors[])(void) = {
    (void (*)(void))(&_estack), /* The initial stack pointer */
    Reset_Handler,              /* The reset handler */
    Default_Handler,            /* NMI Handler */
    Default_Handler,            /* Hard Fault Handler */
    Default_Handler,            /* MPU Fault Handler */
    Default_Handler,            /* Bus Fault Handler */
    Default_Handler,            /* Usage Fault Handler */
    0,                          /* Reserved */
    0,                          /* Reserved */
    0,                          /* Reserved */
    0,                          /* Reserved */
    Default_Handler,            /* SVCall Handler */
    Default_Handler,            /* Debug Monitor Handler */
    0,                          /* Reserved */
    Default_Handler,            /* PendSV Handler */
    Default_Handler,            /* SysTick Handler */
};
