#include "stm32l47xx_i2c_driver.h"
#include "stm32l47xx.h"
#include "stm32l475xx_gpio_driver.h"

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pI2Cx == I2C1) {
            // I2C1_PCLK_EN();  // si lo tuvieras
        } else if (pI2Cx == I2C2) {
            I2C2_PCLK_EN();
        } else if (pI2Cx == I2C3) {
            I2C3_PCLK_EN();
        }
    }
    else
    {
        if (pI2Cx == I2C2) {
            I2C2_PCLK_DI();
        }
        // etc si querés
    }
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    // 0. Configurar GPIO PB10 (SCL) y PB11 (SDA) en modo AF4 open-drain pull-up

    GPIO_Handle_t GpioI2C;

    // PB10 -> SCL
    GpioI2C.pGPIOx = GPIOB;
    GpioI2C.GPIO_PinConfig.GPIO_PinNumber      = 10;
    GpioI2C.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTFN;   // Alternate function
    GpioI2C.GPIO_PinConfig.GPIO_PinAltFunMode  = 4;                 // AF4 = I2C2
    GpioI2C.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_OD;   // open-drain
    GpioI2C.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;       // pull-up
    GpioI2C.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_MEDIUM;    // velocidad media

    GPIO_Init(&GpioI2C);

    // PB11 -> SDA
    GpioI2C.pGPIOx = GPIOB;
    GpioI2C.GPIO_PinConfig.GPIO_PinNumber      = 11;
    GpioI2C.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTFN;
    GpioI2C.GPIO_PinConfig.GPIO_PinAltFunMode  = 4;                 // AF4 = I2C2
    GpioI2C.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_OD;   // open-drain
    GpioI2C.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;       // pull-up
    GpioI2C.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_MEDIUM;

    GPIO_Init(&GpioI2C);

    // 1. Habilitar el clock del periférico I2C
    I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

    // 2. Deshabilitar el periférico I2C antes de configurar
    pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);

    // 3. Configurar filtros
    pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ANFOFF);            // ANFOFF = 0 -> filtro analógico ON
    pI2CHandle->pI2Cx->CR1 &= ~(0xF << I2C_CR1_DNF);             // DNF[3:0] = 0000 -> sin filtro digital

    // 4. Configurar TIMINGR
    // OJO: este timing (0x00303D5B) asume reloj I2C kernel ~16MHz y queremos ~100kHz.
    // Por ahora lo dejamos así. Si después WHO_AM_I no da bien, afinamos timing.
    pI2CHandle->pI2Cx->TIMINGR = 0x00303D5B;

    // 5. Clock stretching permitido
    pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_NOSTRETCH);

    // 6. Habilitar el periférico I2C
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_PE);
}



