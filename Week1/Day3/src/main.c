#include <stdint.h>

#define SCB_VTOR (*(volatile uint32_t *)0xE000ED08UL)
#define PERIPH_BASE        0x40000000UL
#define AHB2PERIPH_BASE    (PERIPH_BASE + 0x08000000UL)

#define GPIOB_BASE         (AHB2PERIPH_BASE + 0x0400UL)
#define RCC_BASE           0x40021000UL

#define RCC_AHB2ENR        (*(volatile uint32_t *)(RCC_BASE + 0x4C))
#define GPIOB_MODER        (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR          (*(volatile uint32_t *)(GPIOB_BASE + 0x14))

#define SYST_CSR           (*(volatile uint32_t *)0xE000E010UL)
#define SYST_RVR           (*(volatile uint32_t *)0xE000E014UL)
#define SYST_CVR           (*(volatile uint32_t *)0xE000E018UL)

#define LED_PIN 14

/* === NUEVO: no usamos ms_ticks ni delay_ms === */
/* la ISR togglea el LED directamente */
void SysTick_Handler(void)
{
    GPIOB_ODR ^= (1u << LED_PIN);
}

void SystemInit(void){
    
}


int main(void)
{
     extern void SystemInit(void);
    RCC_AHB2ENR |= (1u << 1);

    /* PB14 como salida */
    GPIOB_MODER &= ~(3u << (LED_PIN * 2));
    GPIOB_MODER |=  (1u << (LED_PIN * 2));

    /* configurar SysTick para interrumpir MUY rápido
       - recarga chica para que se note a ojo
       - ENABLE + TICKINT + CLKSOURCE = 0x07
    */
    SYST_RVR = 2000 - 1;
    SYST_CVR = 0;
    SYST_CSR = 0x07;

    /* bucle principal vacío: no hacemos nada más */
    while (1)
    {
        /* vacío a propósito */
    }
}