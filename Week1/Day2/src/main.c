#include <stdint.h>

#define PERIPH_BASE         0x40000000UL
#define AHB2PERIPH_BASE    (PERIPH_BASE + 0x08000000UL)

#define GPIOB_BASE         (AHB2PERIPH_BASE + 0x0400UL) // GPIOB offset en L4
#define RCC_BASE           (0x40021000UL)

#define RCC_AHB2ENR        (*(volatile uint32_t *)(RCC_BASE + 0x4C))
#define GPIOB_MODER        (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR          (*(volatile uint32_t *)(GPIOB_BASE + 0x14))

static void delay(volatile uint32_t t)
{
    while (t--) {
        __asm__ volatile ("nop");
    }
}

int main(void)
{
    /* 1. Habilitar clock para GPIOB
       En RCC_AHB2ENR, el bit 1 habilita GPIOB */
    RCC_AHB2ENR |= (1u << 1);

    /* 2. Configurar PB14 como salida push-pull
       Cada pin usa 2 bits en MODER.
       PB14 → bits [28:29] (14 * 2 = 28)
       00 = input
       01 = output
       10 = alternate
       11 = analog
    */
    GPIOB_MODER &= ~(3u << (14 * 2));  // limpio bits 28-29
    GPIOB_MODER |=  (1u << (14 * 2));  // pongo 01 = output

    /* 3. Loop de parpadeo */
    while (1)
    {
        GPIOB_ODR ^= (1u << 14); // toggle PB14
        delay(200000);
    }
}