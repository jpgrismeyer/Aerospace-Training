#include "stm32l47xx_i2c_driver.h"
#include "stm32l47xx.h"
#include "stm32l475xx_gpio_driver.h"


/*
 * stm32l47xx_i2c_driver.c
 *
 *  Created on: May 24, 2025
 *      Author: admin
 */


/*
 * stm32l475xx_i2c_driver.c
 *
 *  Created on: May 2025
 *      Author: Juan Pablo Grismeyer
 */

/*
 * stm32l475xx_i2c_driver.c
 *
 *  Created on: May 2025
 *      Author: Juan Pablo Grismeyer
 */

#include "stm32l47xx_i2c_driver.h"





void I2C_MasterSendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{

	    // Esperar BUSY=0
	    while (pI2Cx->ISR & I2C_ISR_BUSY);

	    // Limpiar CR2
	    pI2Cx->CR2 &= ~(0x3FF | (1 << 10) | (1 << 11) | (1 << 12) | (0xFF << 16) | (1 << 25) | (1 << 13));

	    uint32_t tmpreg = 0;
	    tmpreg |= (SlaveAddr << I2C_CR2_SADD);   // SADD[9:0]
	    // RD_WRN=0 (write), ADD10=0, HEAD10R=0
	    tmpreg |= (Len << I2C_CR2_NBYTES);       // NBYTES
	    if (Sr) {
	        // Repeated START luego → sin AUTOEND
	        // tmpreg &= ~(1 << I2C_CR2_AUTOEND); // ya es 0 por defecto
	    } else {
	        tmpreg |= (1 << I2C_CR2_AUTOEND);    // STOP automático
	    }
	    tmpreg |= (1 << I2C_CR2_START);

	    pI2Cx->CR2 |= tmpreg;

	    // Enviar bytes
	    for (uint32_t i = 0; i < Len; i++)
	    {
	        // Esperar TXIS o NACKF
	        while (!(pI2Cx->ISR & (I2C_ISR_TXIS | I2C_ISR_NACKF)));
	        if (pI2Cx->ISR & I2C_ISR_NACKF) {
	            pI2Cx->ICR |= I2C_ICR_NACKCF;
	            // Esperar STOP y limpiar para dejar limpio
	            while (!(pI2Cx->ISR & I2C_ISR_STOPF));
	            pI2Cx->ICR |= I2C_ICR_STOPCF;
	            return; // abort
	        }
	        pI2Cx->TXDR = pTxBuffer[i];
	    }

	    if (Sr) {
	        // Esperar TC (no STOP) para poder encadenar un START de lectura
	        while (!(pI2Cx->ISR & I2C_ISR_TC)) {
	            if (pI2Cx->ISR & I2C_ISR_NACKF) {
	                pI2Cx->ICR |= I2C_ICR_NACKCF;
	                return;
	            }
	        }
	        return;
	    } else {
	        // Transferencia completa con STOP
	        while (!(pI2Cx->ISR & I2C_ISR_STOPF));
	        pI2Cx->ICR |= I2C_ICR_STOPCF;
	    }

	}



void I2C_MasterReceiveData(I2C_RegDef_t *pI2Cx, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	while (pI2Cx->ISR & I2C_ISR_BUSY);

	    pI2Cx->CR2 &= ~(0x3FF | (1 << 10) | (1 << 11) | (1 << 12) | (0xFF << 16) | (1 << 25) | (1 << 13));

	    uint32_t tmpreg = 0;
	    tmpreg |= (SlaveAddr << I2C_CR2_SADD);
	    tmpreg |= (1 << I2C_CR2_RD_WRN);         // read
	    tmpreg |= (Len << I2C_CR2_NBYTES);
	    tmpreg |= (1 << I2C_CR2_AUTOEND);        // STOP automático al final del read
	    tmpreg |= (1 << I2C_CR2_START);

	    pI2Cx->CR2 |= tmpreg;

	    for (uint32_t i = 0; i < Len; i++)
	    {
	        while (!(pI2Cx->ISR & (I2C_ISR_RXNE | I2C_ISR_NACKF)));
	        if (pI2Cx->ISR & I2C_ISR_NACKF) {
	            pI2Cx->ICR |= I2C_ICR_NACKCF;
	            break;
	        }
	        pRxBuffer[i] = pI2Cx->RXDR;
	    }

	    while (!(pI2Cx->ISR & I2C_ISR_STOPF));
	    pI2Cx->ICR |= I2C_ICR_STOPCF;
	}

int I2C_MemRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t Reg, uint8_t *pBuf, uint32_t Len)
{
   // I2C_MasterSendData(pI2Cx, &Reg, 1, SlaveAddr);    // write reg, sin STOP
    //I2C_MasterReceiveData(pI2Cx, pBuf, Len, SlaveAddr);// read con STOP
    return 0;
}

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





