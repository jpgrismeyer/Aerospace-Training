/*
 * stm32l47xx_systick.c
 *
 *  Created on: May 23, 2025
 *      Author: admin
 */



#include "stm32l475xx_systick.h"


// Definiciones directas según el Cortex-M4 TRM
#define SYST_CSR   (*((volatile uint32_t*)0xE000E010))
#define SYST_RVR   (*((volatile uint32_t*)0xE000E014))
#define SYST_CVR   (*((volatile uint32_t*)0xE000E018))
// #define SYST_CALIB (*((volatile uint32_t*)0xE000E01C)) // opcional

void systick_init(uint32_t ticks) {
    SYST_RVR = ticks - 1;      // Valor de recarga
    SYST_CVR = 0;              // Reset contador
    SYST_CSR = (1 << 0) | (1 << 2);  // ENABLE + CLKSOURCE = processor clock
    // Bit 0 = ENABLE, Bit 2 = CLKSOURCE (1 = core)
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        systick_init(16000);  // 1 ms @ 16 MHz
        while ((SYST_CSR & (1 << 16)) == 0); // Wait for COUNTFLAG
    }
}



