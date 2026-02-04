/*
 * stm32l475xx_gpio_driver.h
 *
 *  Created on: Jan 26, 2025
 *      Author: admin
 */

#ifndef INC_STM32L475XX_GPIO_DRIVER_H_
#define INC_STM32L475XX_GPIO_DRIVER_H_

#include"stm32l47xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;				/*<Possible modes from @GPIO_PIN_MODES>*/
	uint8_t GPIO_PinSpeed;				/*<Possible modes from @GPIO_PIN_SPEED>*/
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

/*
 * This is the handle structure for a GPIO pin
 */

typedef struct
{
	GPIO_RegDef_t *pGPIOx;				/*Holds the base address of the GPIO port to which the pin belongs*/
	GPIO_PinConfig_t GPIO_PinConfig;	/*Holds GPIO pin configuration settings*/
}GPIO_Handle_t;


/* @GPIO_PIN_NUMBER
 * Gpio pin numbers
 */

#define GPIO_PIN_NO_0 		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2 		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4 		4
#define GPIO_PIN_NO_5 		5
#define GPIO_PIN_NO_6 		6
#define GPIO_PIN_NO_7 		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9 		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11 		11
#define GPIO_PIN_NO_12 		12
#define GPIO_PIN_NO_13 		13
#define GPIO_PIN_NO_14 		14
#define GPIO_PIN_NO_15		15


/* @GPIO_PIN_MODES
 * Gpio pin possible modes
 */

#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG 	3
#define GPIO_MODE_IT_FT 	4	/*Interrupt*/
#define GPIO_MODE_IT_RT 	5	/*Interrupt*/
#define GPIO_MODE_IT_RFT 	6	/*Interrupt*/

/*
 * GPIO pin possible output types
 */

#define GPIO_OP_TYPE_PP 	0   /*PUSH PULL*/
#define GPIO_OP_TYPE_OD		1	/*OPEN DRAIN*/

/* @GPIO_PIN_SPEED
 * GPIO pin possible output speed
 */

#define GPIO_SPEED_LOW 			0   /*See frequency specifications*/
#define GPIO_SPEED_MEDIUM 		1   /*See frequency specifications*/
#define GPIO_SPEED_FAST 		2   /*See frequency specifications*/
#define GPIO_SPEED_HIGH 		3   /*See frequency specifications*/

/*
 * GPIO pin pull up and pull down conf macros
 */

#define GPIO_NO_PUPD 			0
#define GPIO_PIN_PU 			1
#define GPIO_PIN_PD		 		2



/*Peripheral Clock setup
 *
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 *Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 *Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);

/*
 *IRQ Configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32L475XX_GPIO_DRIVER_H_ */
