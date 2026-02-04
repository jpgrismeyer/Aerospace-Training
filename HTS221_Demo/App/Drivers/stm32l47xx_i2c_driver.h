/*
 * stm32l47xx_i2c_driver.h
 *
 *  Created on: May 24, 2025
 *      Author: admin
 */

#ifndef INC_STM32L47XX_I2C_DRIVER_H_
#define INC_STM32L47XX_I2C_DRIVER_H_


#include "stm32l47xx.h"

typedef struct
{
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_NoStretch;
	uint32_t I2C_FMDutyCycle;
} I2C_Config_t;

typedef struct
{
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2CConfig;
} I2C_Handle_t;

#define I2C_ACK_ENABLE    1
#define I2C_ACK_DISABLE   0

#define I2C_SCL_SPEED_SM  100000

#define I2C_NOSTRETCH_ENABLE   1
#define I2C_NOSTRETCH_DISABLE  0

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

void I2C_MasterSendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterReceiveData(I2C_RegDef_t *pI2Cx, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

int I2C_MemRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t Reg, uint8_t *pBuf, uint32_t Len);




#endif /* INC_STM32L47XX_I2C_DRIVER_H_ */
