/*
 * stm32l475xx_gpio_driver.c
 *
 *  Created on: Jan 26, 2025
 *      Author: admin
 */

#include"stm32l475xx_gpio_driver.h"

/**********************************************************
 * @fn									-	GPIO_PeriClockControl
 *
 * @brief								-	this function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]							-	base address of the gpio peripheral
 * @param[in]							-	ENABLE or DISABLE macros
 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi==ENABLE)
	{
		if(pGPIOx==GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if (pGPIOx==GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIOx==GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx==GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIOx==GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if (pGPIOx==GPIOF)
		{
			GPIOF_PCLK_EN();
		}else if (pGPIOx==GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if (pGPIOx==GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}

	else if(EnorDi==DISABLE)
		{
			if(pGPIOx==GPIOA)
			{
				GPIOA_PCLK_DI();
			}else if (pGPIOx==GPIOB)
			{
				GPIOB_PCLK_DI();
			}else if (pGPIOx==GPIOC)
			{
				GPIOC_PCLK_DI();
			}else if (pGPIOx==GPIOD)
			{
				GPIOD_PCLK_DI();
			}else if (pGPIOx==GPIOE)
			{
				GPIOE_PCLK_DI();
			}else if (pGPIOx==GPIOF)
			{
				GPIOF_PCLK_DI();
			}else if (pGPIOx==GPIOG)
			{
				GPIOG_PCLK_DI();
			}else if (pGPIOx==GPIOH)
			{
				GPIOH_PCLK_DI();
			}
		}

}

/**********************************************************
 * @fn									-	GPIO_Init
 *
 * @brief								-	Initialises GPIO pin
 *

 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0; //temp register

	//enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	// 1. Configure the mode of GPIO pin
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<=GPIO_MODE_ANALOG)
	//The none interrupt mode
	{
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER&=~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
		pGPIOHandle->pGPIOx->MODER|=temp; //setting

	}else
	{
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_FT)
		{
			//1. Configure FTSR
			pGPIOHandle->pGPIOx->MODER&=~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
			pGPIOHandle->pGPIOx->MODER|=0x0; //setting

			EXTI->FTSR1 |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->RTSR1 &= ~(1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); //Clear corresponding rtsr bit
		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RT)
		{
			pGPIOHandle->pGPIOx->MODER&=~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
			pGPIOHandle->pGPIOx->MODER|=0x0; //setting

			//1. COnfigure RTSR
			EXTI->RTSR1 |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->FTSR1 &= ~(1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); //Clear corresponding ftsr bit
		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RFT)
		{
			//1. Configure both FTSR and RTSR
			EXTI->FTSR1 |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->RTSR1 |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}


		// 2. Configure GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;  // Índice del registro EXTICR
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;  // Índice del campo dentro del registro
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);   // Código del puerto GPIO

		// Habilitar el reloj para SYSCFG
		SYSCFG_PCLK_EN();

		// Limpiar el campo correspondiente a EXTI2 y asignar el código del puerto
		SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2 * 4));  // Limpiar el campo
		SYSCFG->EXTICR[temp1] |= (portcode << (temp2 * 4));  // Asignar el código del puerto

		// 3. Enable the EXTI interrupt delivery using IMR
		EXTI->IMR1 |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;  // Habilitar la máscara de interrupción
	}
	temp=0;

	//2. Configure the speed
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->OSPEEDR&=~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
		pGPIOHandle->pGPIOx->OSPEEDR|=temp; //setting
		temp=0;

	//3. Configure pupd settings
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->PUPDR&=~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
		pGPIOHandle->pGPIOx->PUPDR|=temp;   //no se tocan otros bits del registro (|=)
		temp=0;
	//4. Configure otype
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->OTYPER&=~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
		pGPIOHandle->pGPIOx->OTYPER|=temp;
		temp=0;
	//5. Configure the alt functionality
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_ALTFN)
	{
		//Configure the alt function registers
		uint32_t temp1, temp2;
		temp1=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/8;
		temp2=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF<<(4 * temp2));  //clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode<<(4*temp2)); //setting
	}
}

/**********************************************************
 * @fn									-	GPIO_DeInit
 *
 * @brief								-	Reset GPIO pin
 *

 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx==GPIOA)
			{
				GPIOA_REG_RESET();
			}else if (pGPIOx==GPIOB)
			{
				GPIOB_REG_RESET();
			}else if (pGPIOx==GPIOC)
			{
				GPIOC_REG_RESET();
			}else if (pGPIOx==GPIOD)
			{
				GPIOD_REG_RESET();
			}else if (pGPIOx==GPIOE)
			{
				GPIOE_REG_RESET();
			}else if (pGPIOx==GPIOF)
			{
				GPIOF_REG_RESET();
			}else if (pGPIOx==GPIOG)
			{
				GPIOG_REG_RESET();
			}else if (pGPIOx==GPIOH)
			{
				GPIOH_REG_RESET();
			}
}

/**********************************************************
 * @fn									-	GPIO_ReadFromInputPin
 *
 * @brief								-
 *

 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */

uint8_t GPIO_ReadFromInputPin (GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	uint8_t value;
	value= (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);

	return value;
}

/**********************************************************
 * @fn									-	GPIO_ReadFromInputPort
 *
 * @brief								-
 *

 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */

uint16_t GPIO_ReadFromInputPort (GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value= (uint16_t)pGPIOx->IDR;

	return value;
}

/**********************************************************
 * @fn									-	GPIO_WriteToOutputPin
 *
 * @brief								-
 *

 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET)
	{
		//Write 1 to the output data register at the bit field corresponding to the pin
		pGPIOx->ODR |= (1 << PinNumber);

	}else
	{
		//write 0
		pGPIOx->ODR &= ~(1<< PinNumber);
	}
}

/**********************************************************
 * @fn									-	GPIO_WriteToOutputPort
 *
 * @brief								-
 *

 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}

/**********************************************************
 * @fn									-	GPIO_ToggleOutputPin
 *
 * @brief								-
 *

 *
 * @return								-	None
 *
 * @Note								-	none
 *
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber); //Xor con 1
}

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi== ENABLE)
	{
		if (IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);

		}else if (IRQNumber > 31 && IRQNumber < 64)
		{
			//program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			//program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}

	}else
	{
		if (IRQNumber <= 31)
				{
					//program ICER0 register
					*NVIC_ICER0 |= (1 << IRQNumber);

				}else if (IRQNumber > 31 && IRQNumber < 64)
				{
					//program ICER1 register
					*NVIC_ICER1 |= (1 << (IRQNumber % 32));
				}else if (IRQNumber >= 64 && IRQNumber < 96)
				{
					//program ICER2 register
					*NVIC_ICER2 |= (1 << (IRQNumber % 64));
				}

	}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//1. find ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = ( 8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + (iprx)) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the exti pr register corresponding to the pin number
	if (EXTI->PR1 & (1 << PinNumber))
	{
		//clear
		EXTI->PR1 |= (1<< PinNumber);

	}
}

