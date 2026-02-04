/*
 * stm32l47xx.h
 *
 *  Created on: Jan 22, 2025
 *      Author: admin
 */

#ifndef INC_STM32L47XX_H_
#define INC_STM32L47XX_H_
#include<stdint.h>

// SysTick
#define SYST_CSR        ((__vo uint32_t*)0xE000E010))
#define SYST_RVR        ((__vo uint32_t*)0xE000E014))
#define SYST_CVR        ((__vo uint32_t*)0xE000E018))
#define SYST_CALIB      ((__vo uint32_t*)0xE000E01C))

/*
*ARM Cortex Mx Processor NVIC ISERx register addresses
*/


#define NVIC_ISER0						((__vo uint32_t*) 0xE000E100)
#define NVIC_ISER1						((__vo uint32_t*) 0xE000E104)
#define NVIC_ISER2						((__vo uint32_t*) 0xE000E108)
#define NVIC_ISER3						((__vo uint32_t*) 0xE000E10C)

/*
*ARM Cortex Mx Processor NVIC ICERx register addresses
*/

#define NVIC_ICER0						((__vo uint32_t*) 0xE000E180)
#define NVIC_ICER1						((__vo uint32_t*) 0xE000E184)
#define NVIC_ICER2						((__vo uint32_t*) 0xE000E188)
#define NVIC_ICER3						((__vo uint32_t*) 0xE000E18C)

/*
*ARM Cortex Mx Processor Priority register Address calculation
*/

#define NVIC_PR_BASE_ADDR						((__vo uint32_t*) 0xE000E400)
#define NO_PR_BITS_IMPLEMENTED			4


#define FLASH_BASEADDR 					0x08000000U
#define SRAM1_BASEADDR					0x20000000U
#define SRAM2_BASEADDR					0x10000000U
#define ROM_BASEADDR 					0x1FFF0000U /* aka System Memory*/
#define SRAM_BASEADDR					SRAM1_BASEADDR
#define __vo volatile


/*
*AHBx and APBx Bus Peripheral base addresses
*/

#define PERIPH_BASEADDR					0x40000000U
#define APB1PERIPH_BASEADDR				0x40000000U
#define APB2PERIPH_BASEADDR				0x40010000U
#define AHB1PERIPH_BASEADDR				0x40020000U
#define AHB2PERIPH_BASEADDR				0x48000000U
#define AHB3PERIPH_BASEADDR				0xA0000000U

/*
 * Base addresses of peripherals which are hanging on AHB1 Bus
 */
#define	DMA1_BASEADDR					0x40020000U
#define	DMA2_BASEADDR					0x40020400U
#define	RCC_BASEADDR					0x40021000U
#define	FLASHREG_BASEADDR				0x40022000U
#define	CRC_BASEADDR					0x40023000U
#define	TSC_BASEADDR					0x40024000U

/*
 * Base addresses of peripherals which are hanging on AHB2 Bus
 */
#define	GPIOA_BASEADDR					0x48000000U
#define	GPIOB_BASEADDR					0x48000400U
#define	GPIOC_BASEADDR					0x48000800U
#define	GPIOD_BASEADDR					0x48000C00U
#define	GPIOE_BASEADDR					0x48001000U
#define	GPIOF_BASEADDR					0x48001400U
#define	GPIOG_BASEADDR					0x48001800U
#define	GPIOH_BASEADDR					0x48001C00U
#define	OTG_FS_BASEADDR					0x50000000U
#define	ADC_BASEADDR					0x50040000U
#define	RNG_BASEADDR					0x50060800U

/*
 * Base addresses of peripherals which are hanging on AHB3 Bus
 */
#define	FMC_BASEADDR					0xA0000000U
#define	QUADSPI_BASEADDR				0xA0001000U

/*
 * Base addresses of peripherals which are hanging on APB1 Bus
 * I2C1 I2C2 I2C3 SPI2 SPI3 USART2 USART3 UART4 UART5
 */
#define	SPI2_BASEADDR					0x40003800U
#define	SPI3_BASEADDR					0x40003C00U
#define	USART2_BASEADDR					0x40004400U
#define	USART3_BASEADDR					0x40004800U
#define	UART4_BASEADDR					0x40004C00U
#define	UART5_BASEADDR					0x40005000U
#define	I2C1_BASEADDR					0x40005400U
#define	I2C2_BASEADDR					0x40005800U
#define	I2C3_BASEADDR					0x40005C00U
#define	CAN1_BASEADDR					0x40006400U

/*
 * Base addresses of peripherals which are hanging on APB2 Bus
 * SPI1 USART1 USART6 EXTI SYSCFG
 * NO TIENE USART6
 */
#define	SYSCFG_BASEADDR					0x40010000U
#define	EXTI_BASEADDR					0x40010400U
#define	SPI1_BASEADDR					0x40013000U
#define	USART1_BASEADDR					0x40013800U

/*
 * Peripheral register definition structure for GPIO
 */

typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
	__vo uint32_t BRR;
	__vo uint32_t ASCR;
}GPIO_RegDef_t;

/*
 * Peripheral register definition structure for SPI
 */

typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
}SPI_RegDef_t;

/*
 * Peripheral register definition structure for I2C
 */

typedef struct
{
	__vo uint32_t CR1;        // Control register 1           - Offset 0x00
	__vo uint32_t CR2;        // Control register 2           - Offset 0x04
	__vo uint32_t OAR1;       // Own address register 1       - Offset 0x08
	__vo uint32_t OAR2;       // Own address register 2       - Offset 0x0C
	__vo uint32_t TIMINGR;    // Timing register              - Offset 0x10
	__vo uint32_t TIMEOUTR;   // Timeout register             - Offset 0x14
	__vo uint32_t ISR;        // Interrupt and status reg     - Offset 0x18
	__vo uint32_t ICR;        // Interrupt clear register     - Offset 0x1C
	__vo uint32_t PECR;       // PEC register                 - Offset 0x20
	__vo uint32_t RXDR;       // Receive data register        - Offset 0x24
	__vo uint32_t TXDR;       // Transmit data register       - Offset 0x28
} I2C_RegDef_t;

/*
 * Peripheral register definition structure for USART
 */

typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t BRR;
	__vo uint32_t GTPR;
	__vo uint32_t RTOR;
	__vo uint32_t RQR;
	__vo uint32_t ISR;
	__vo uint32_t ICR;
	__vo uint32_t RDR;
	__vo uint32_t TDR;
} USART_RegDef_t;



/*
 * Peripheral register definition structure for ADC
 */

typedef struct
{
  __vo uint32_t ISR;
  __vo uint32_t IER;
  __vo uint32_t CR;
  __vo uint32_t CFGR;
  __vo uint32_t RESERVED0;
  __vo uint32_t SMPR1;
  __vo uint32_t SMPR2;
  __vo uint32_t RESERVED1[2];
  __vo uint32_t TR1;
  __vo uint32_t TR2;
  __vo uint32_t TR3;
  __vo uint32_t SQR1;
  __vo uint32_t SQR2;
  __vo uint32_t SQR3;
  __vo uint32_t SQR4;
  __vo uint32_t DR;
  __vo uint32_t RESERVED2[2];
  __vo uint32_t JSQR;
  __vo uint32_t RESERVED3[4];
  __vo uint32_t OFR1;
  __vo uint32_t OFR2;
  __vo uint32_t OFR3;
  __vo uint32_t OFR4;
  __vo uint32_t RESERVED4[4];
  __vo uint32_t JDR1;
  __vo uint32_t JDR2;
  __vo uint32_t JDR3;
  __vo uint32_t JDR4;
  __vo uint32_t RESERVED5[4];
  __vo uint32_t AWD2CR;
  __vo uint32_t AWD3CR;
  __vo uint32_t RESERVED6[2];
  __vo uint32_t DIFSEL;
  __vo uint32_t CALFACT;
} ADC_RegDef_t;

/*
 * Peripheral register definition structure for RCC
 */
typedef struct
{
	__vo uint32_t CR;								/*0x00*/
	__vo uint32_t ICSCR;							/*0x04*/
	__vo uint32_t CFGR;								/*0x08*/
	__vo uint32_t PLLCFGR;							/*0x0C*/
	__vo uint32_t PLLSAI1CFGR;						/*0x10*/
	__vo uint32_t PLLSAI2CFGR;						/*0x14*/
	__vo uint32_t CIER;								/*0x18*/
	__vo uint32_t CIFR;								/*0x1C*/
	__vo uint32_t CICR;								/*0x20*/
	__vo uint32_t RESERVED0;						/*0x24*/
	__vo uint32_t AHB1RSTR;							/*0x28*/
	__vo uint32_t AHB2RSTR;							/*0x2C*/
	__vo uint32_t AHB3RSTR;							/*0x30*/
	__vo uint32_t RESERVED1;						/*0x34*/
	__vo uint32_t APB1RSTR1;						/*0x38*/
	__vo uint32_t APB1RSTR2;						/*0x3C*/
	__vo uint32_t APB2RSTR;							/*0x40*/
	__vo uint32_t RESERVED2;						/*0x44*/
	__vo uint32_t AHB1ENR;							/*0x48*/
	__vo uint32_t AHB2ENR;							/*0x4C*/
	__vo uint32_t AHB3ENR;							/*0x50*/
	__vo uint32_t RESERVED3;						/*0x54*/
	__vo uint32_t APB1ENR1;							/*0x58*/
	__vo uint32_t APB1ENR2;							/*0x5C*/
	__vo uint32_t APB2ENR;							/*0x60*/
	__vo uint32_t RESERVED4;						/*0x64*/
	__vo uint32_t AHB1SMENR;						/*0x68*/
	__vo uint32_t AHB2SMENR;						/*0x6C*/
	__vo uint32_t AHB3SMENR;						/*0x70*/
	__vo uint32_t RESERVED5;						/*0x74*/
	__vo uint32_t APB1SMENR1;						/*0x78*/
	__vo uint32_t APB1SMENR2;						/*0x7C*/
	__vo uint32_t APB2SMENR;						/*0x80*/
	__vo uint32_t RESERVED6;						/*0x84*/
	__vo uint32_t CCIPR;							/*0x88*/
	__vo uint32_t RESERVED7;						/*0x8C*/
	__vo uint32_t BDCR;								/*0x90*/
	__vo uint32_t CSR;								/*0x94*/
}RCC_RegDef_t;

/*
 * Peripheral register definition structure for EXTI
 */
typedef struct
{
	__vo uint32_t IMR1;
	__vo uint32_t EMR1;
	__vo uint32_t RTSR1;
	__vo uint32_t FTSR1;
	__vo uint32_t SWIER1;
	__vo uint32_t PR1;
	__vo uint32_t RESERVED0;
	__vo uint32_t RESERVED1;
	__vo uint32_t IMR2;
	__vo uint32_t EMR2;
	__vo uint32_t RTSR2;
	__vo uint32_t FTSR2;
	__vo uint32_t SWIER2;
	__vo uint32_t PR2;
}EXTI_RegDef_t;

/*
 * Peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t CFGR1;
	__vo uint32_t EXTICR[4];
	__vo uint32_t SCSR;
	__vo uint32_t CFGR2;
	__vo uint32_t SWPR;
	__vo uint32_t SKR;
	__vo uint32_t SWPR2;
	
}SYSCFG_RegDef_t;



/*
 * peripheral definitions (peripheral base addresses typecasted to xxx_RegDef_t)
 */
#define GPIOA 					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB 					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC 					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD 					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE 					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF 					((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG 					((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH 					((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define SPI1 					((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2 					((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3 					((SPI_RegDef_t*)SPI3_BASEADDR)

#define I2C1    				((I2C_RegDef_t*) I2C1_BASEADDR)
#define I2C2    				((I2C_RegDef_t*) I2C2_BASEADDR)
#define I2C3    				((I2C_RegDef_t*) I2C3_BASEADDR)

#define USART1  				((USART_RegDef_t*) USART1_BASEADDR)
#define USART2  				((USART_RegDef_t*) USART2_BASEADDR)
#define USART3  				((USART_RegDef_t*) USART3_BASEADDR)
#define UART4  					((USART_RegDef_t*) UART4_BASEADDR)
#define UART5  					((USART_RegDef_t*) UART5_BASEADDR)




#define ADC1  					((ADC_RegDef_t*) ADC_BASEADDR)

#define RCC 					((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI					((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG					((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*
 * Clock enable macros for GPIOx peripherals (AHB2)
 */
#define GPIOA_PCLK_EN()		(RCC->AHB2ENR|=(1<<0))     /*Habilito el clock para gpioA (bit 0)*/
#define GPIOB_PCLK_EN()		(RCC->AHB2ENR|=(1<<1))     /*Habilito el clock para gpioB (bit 1)*/
#define GPIOC_PCLK_EN()		(RCC->AHB2ENR|=(1<<2))     /*Habilito el clock para gpioC (bit 2)*/
#define GPIOD_PCLK_EN()		(RCC->AHB2ENR|=(1<<3))     /*Habilito el clock para gpioD (bit 3)*/
#define GPIOE_PCLK_EN()		(RCC->AHB2ENR|=(1<<4))     /*Habilito el clock para gpioE (bit 4)*/
#define GPIOF_PCLK_EN()		(RCC->AHB2ENR|=(1<<5))     /*Habilito el clock para gpioF (bit 5)*/
#define GPIOG_PCLK_EN()		(RCC->AHB2ENR|=(1<<6))     /*Habilito el clock para gpioG (bit 6)*/
#define GPIOH_PCLK_EN()		(RCC->AHB2ENR|=(1<<7))     /*Habilito el clock para gpioH (bit 7)*/

/*
 * Clock enable macros for I2Cx peripherals (APB1)
 */
#define I2C1_PCLK_EN()		(RCC->APB1ENR1|=(1<<21))     /*Habilito el clock para I2C1 (bit 21)*/
#define I2C2_PCLK_EN()		(RCC->APB1ENR1|=(1<<22))     /*Habilito el clock para I2C2 (bit 22)*/
#define I2C3_PCLK_EN()		(RCC->APB1ENR1|=(1<<23))     /*Habilito el clock para I2C3 (bit 23)*/

/*
 * Clock enable macros for SPIx peripherals (APB1 and APB2)
 */
#define SPI1_PCLK_EN()		(RCC->APB2ENR|=(1<<12))     /*Habilito el clock para SPI1 (bit 12)*/
#define SPI2_PCLK_EN()		(RCC->APB1ENR1|=(1<<14))     /*Habilito el clock para SPI2 (bit 14)*/
#define SPI3_PCLK_EN()		(RCC->APB1ENR1|=(1<<15))     /*Habilito el clock para SPI3 (bit 15)*/

/*
 * Clock enable macros for USARTx peripherals (APB1 and APB2)
 */
#define USART1_PCLK_EN()		(RCC->APB2ENR|=(1<<14))     /*Habilito el clock para USART1 (bit 14)*/
#define USART2_PCLK_EN()		(RCC->APB1ENR1|=(1<<17))     /*Habilito el clock para USART2 (bit 17)*/
#define USART3_PCLK_EN()		(RCC->APB1ENR1|=(1<<18))     /*Habilito el clock para USART3 (bit 18)*/
#define UART4_PCLK_EN()			(RCC->APB1ENR1|=(1<<19))
#define UART5_PCLK_EN()			(RCC->APB1ENR1|=(1<<20))

/*
 * Clock enable macros for SYSCFG peripherals (APB2)
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR|=(1<<0))     /*Habilito el clock para SYSCFG (bit 0)*/


/*
 * Clock disable macros for GPIOx peripherals (AHB2)
 */
#define GPIOA_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<0))     /*CLEAR el clock para gpioA (bit 0)*/
#define GPIOB_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<1))     /*CLEAR el clock para gpioB (bit 1)*/
#define GPIOC_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<2))     /*CLEAR el clock para gpioC (bit 2)*/
#define GPIOD_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<3))     /*CLEAR el clock para gpioD (bit 3)*/
#define GPIOE_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<4))     /*CLEAR el clock para gpioE (bit 4)*/
#define GPIOF_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<5))     /*CLEAR el clock para gpioF (bit 5)*/
#define GPIOG_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<6))     /*CLEAR el clock para gpioG (bit 6)*/
#define GPIOH_PCLK_DI()		(RCC->AHB2ENR&= ~(1<<7))     /*CLEAR el clock para gpioH (bit 7)*/

/*
 * Clock disable macros for I2Cx peripherals (APB1)
 */
#define I2C1_PCLK_DI()		(RCC->APB1ENR1&= ~(1<<21))     /*CLEAR el clock para I2C1 (bit 21)*/
#define I2C2_PCLK_DI()		(RCC->APB1ENR1&= ~(1<<22))     /*CLEAR el clock para I2C2 (bit 22)*/
#define I2C3_PCLK_DI()		(RCC->APB1ENR1&= ~(1<<23))     /*CLEAR el clock para I2C3 (bit 23)*/

/*
 * Clock disable macros for SPIx peripherals (APB1 and APB2)
 */
#define SPI1_PCLK_DI()		(RCC->APB2ENR&= ~(1<<12))     /*CLEAR el clock para SPI1 (bit 12)*/
#define SPI2_PCLK_DI()		(RCC->APB1ENR1&= ~(1<<14))     /*CLEAR el clock para SPI2 (bit 14)*/
#define SPI3_PCLK_DI()		(RCC->APB1ENR1&= ~(1<<15))     /*CLEAR el clock para SPI3 (bit 15)*/

/*
 * Clock disable macros for USARTx peripherals (APB1 and APB2)
 */

#define USART1_PCLK_DI()		(RCC->APB2ENR&= ~(1<<14))     /*Habilito el clock para USART1 (bit 14)*/
#define USART2_PCLK_DI()		(RCC->APB1ENR1&= ~(1<<17))     /*Habilito el clock para USART2 (bit 17)*/
#define USART3_PCLK_DI()		(RCC->APB1ENR1&= ~(1<<18))     /*Habilito el clock para USART3 (bit 18)*/
#define UART4_PCLK_DI()			(RCC->APB1ENR1&= ~(1<<19))
#define UART5_PCLK_DI()			(RCC->APB1ENR1&= ~(1<<20))

/*
 * Clock disable macros for SYSCFG peripherals (APB2)
 */
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR&= ~(1<<0))     /*CLEAR el clock para SYSCFG (bit 0)*/

/*
 * Macros for reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<0));		(RCC->AHB2RSTR&=~(1<<0));}while(0)
#define GPIOB_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<1));		(RCC->AHB2RSTR&=~(1<<1));}while(0)
#define GPIOC_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<2));		(RCC->AHB2RSTR&=~(1<<2));}while(0)
#define GPIOD_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<3));		(RCC->AHB2RSTR&=~(1<<3));}while(0)
#define GPIOE_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<4));		(RCC->AHB2RSTR&=~(1<<4));}while(0)
#define GPIOF_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<5));		(RCC->AHB2RSTR&=~(1<<5));}while(0)
#define GPIOG_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<6));		(RCC->AHB2RSTR&=~(1<<6));}while(0)
#define GPIOH_REG_RESET()		do{(RCC->AHB2RSTR|=(1<<7));		(RCC->AHB2RSTR&=~(1<<7));}while(0)



#define GPIO_BASEADDR_TO_CODE(x)	   ((x==GPIOA) ? 0 :\
										(x==GPIOB) ? 1 :\
										(x==GPIOC) ? 2 :\
										(x==GPIOD) ? 3 :\
										(x==GPIOE) ? 4 :\
										(x==GPIOF) ? 5 :\
										(x==GPIOG) ? 6 :\
										(x==GPIOH) ? 7 :0 )

#define SPI1_REG_RESET()		do{(RCC->APB2RSTR|=(1<<12));		(RCC->APB2RSTR&=~(1<<12));}while(0)
#define SPI2_REG_RESET()		do{(RCC->APB1RSTR1|=(1<<14));		(RCC->APB1RSTR1&=~(1<<14));}while(0)
#define SPI3_REG_RESET()		do{(RCC->APB1RSTR1|=(1<<15));		(RCC->APB1RSTR1&=~(1<<15));}while(0)



#define I2C1_REG_RESET()    do{ (RCC->APB1RSTR1 |= (1 << 21)); (RCC->APB1RSTR1 &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()    do{ (RCC->APB1RSTR1 |= (1 << 22)); (RCC->APB1RSTR1 &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()    do{ (RCC->APB1RSTR1 |= (1 << 30)); (RCC->APB1RSTR1 &= ~(1 << 30)); }while(0)

#define USART1_REG_RESET()		do{(RCC->APB1RSTR2|=(1<<0));		(RCC->APB1RSTR2&=~(1<<0));}while(0)
#define USART2_REG_RESET()		do{(RCC->APB1RSTR1|=(1<<17));		(RCC->APB1RSTR1&=~(1<<17));}while(0)
#define USART3_REG_RESET()		do{(RCC->APB1RSTR1|=(1<<18));		(RCC->APB1RSTR1&=~(1<<18));}while(0)
#define UART4_REG_RESET()		do{(RCC->APB2RSTR|=(1<<19));		(RCC->APB2RSTR&=~(1<<19));}while(0)
#define UART5_REG_RESET()		do{(RCC->APB1RSTR1|=(1<<20));		(RCC->APB1RSTR1&=~(1<<20));}while(0)


/*
 * IRQ (Interrupt request) Numbers of STM32L475 MCU
 */

#define IRQ_NO_EXTI0		 6
#define IRQ_NO_EXTI1		 7
#define IRQ_NO_EXTI2		 8
#define IRQ_NO_EXTI3		 9
#define IRQ_NO_EXTI4		 10
#define IRQ_NO_EXTI9_5		 23
#define IRQ_NO_EXTI15_10	 40

/*
 * Macros for all possible priority levels
 */

#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI15		15

//some generic macros
#define ENABLE				 1
#define DISABLE 			 0
#define SET 				 ENABLE
#define RESET 				 DISABLE
#define GPIO_PIN_SET 		 SET
#define GPIO_PIN_RESET 		 RESET
#define FLAG_RESET			 RESET
#define FLAG_SET			 SET

/***************************************************************************************************
 *     BIT POSITIONS DEFINITIONS OF SPI PERIPHERAL
 *************************************************************************************************/
#define SPI_CR1_CPHA 		 0
#define SPI_CR1_CPOL		 1
#define SPI_CR1_MSTR 		 2
#define SPI_CR1_BR			 3
#define SPI_CR1_SPE 		 6
#define SPI_CR1_LSB_FIRST	 7
#define SPI_CR1_SSI 		 8
#define SPI_CR1_SSM		 	 9
#define SPI_CR1_RX_ONLY	 	 10
#define SPI_CR1_CRCL		 11
#define SPI_CR1_CRCN_EXT	 12
#define SPI_CR1_CRCEN		 13
#define SPI_CR1_BIDI_OE	 	 14
#define SPI_CR1_BIDI_MODE	 15

#define SPI_CR2_RXDMAEN 	 0
#define SPI_CR2_TXDMAEN		 1
#define SPI_CR2_SSOE 		 2
#define SPI_CR2_NSSP		 3
#define SPI_CR2_FRF 		 4
#define SPI_CR2_ERRIE	     5
#define SPI_CR2_RXNEIE 		 6
#define SPI_CR2_TXEIE		 7
#define SPI_CR2_DS	 	 	 8
#define SPI_CR2_FRXTH		 12
#define SPI_CR2_LDMA_RX	 	 13
#define SPI_CR2_LDMA_TX		 14

#define SPI_SR_RXNE		 	 0
#define SPI_SR_TXE		 	 1
#define SPI_SR_CRCERR	 	 4
#define SPI_SR_MODF		 	 5
#define SPI_SR_OVR		 	 6
#define SPI_SR_BSY		 	 7
#define SPI_SR_FRE		 	 8
#define SPI_SR_FRLVL	 	 9
#define SPI_SR_FTLVL	 	 11


/***************************************************************************************************
 *     BIT POSITIONS DEFINITIONS OF I2C PERIPHERAL
 *************************************************************************************************/
/***************************************************************************************************
 *     BIT POSITIONS DEFINITIONS OF I2C PERIPHERAL
 *************************************************************************************************/

#define I2C_CR1_PE              0
#define I2C_CR1_TXIE            1
#define I2C_CR1_RXIE            2
#define I2C_CR1_ADDRIE          3
#define I2C_CR1_NACKIE          4
#define I2C_CR1_STOPIE          5
#define I2C_CR1_TCIE            6
#define I2C_CR1_ERRIE           7
#define I2C_CR1_DNF             8  // [11:8] Digital noise filter
#define I2C_CR1_ANFOFF         12
#define I2C_CR1_SWRST          13
#define I2C_CR1_TXDMAEN        14
#define I2C_CR1_RXDMAEN        15
#define I2C_CR1_SBC            16
#define I2C_CR1_NOSTRETCH      17
#define I2C_CR1_WUPEN          18
#define I2C_CR1_GCEN           19
#define I2C_CR1_SMBHEN         20
#define I2C_CR1_SMBDEN         21
#define I2C_CR1_ALERTEN        22
#define I2C_CR1_PECEN          23


#define I2C_CR2_SADD            0   // [9:0] Slave address
#define I2C_CR2_RD_WRN         10
#define I2C_CR2_ADD10          11
#define I2C_CR2_HEAD10R        12
#define I2C_CR2_START          13
#define I2C_CR2_STOP           14
#define I2C_CR2_NACK           15
#define I2C_CR2_NBYTES         16  // [23:16]
#define I2C_CR2_RELOAD         24
#define I2C_CR2_AUTOEND        25
#define I2C_CR2_PECBYTE        26


#define I2C_TIMINGR_SCLL		0
#define I2C_TIMINGR_SCLH		8
#define I2C_TIMINGR_SDADEL		16
#define I2C_TIMINGR_SCLDEL		20
#define I2C_TIMINGR_PRESC		28

#define I2C_ISR_TXE            0
#define I2C_ISR_TXIS           1
#define I2C_ISR_RXNE           2
#define I2C_ISR_ADDR           3
#define I2C_ISR_NACKF          4
#define I2C_ISR_STOPF          5
#define I2C_ISR_TC             6
#define I2C_ISR_TCR            7
#define I2C_ISR_BERR           8
#define I2C_ISR_ARLO           9
#define I2C_ISR_OVR            10
#define I2C_ISR_PECERR         11
#define I2C_ISR_TIMEOUT        12
#define I2C_ISR_ALERT          13
#define I2C_ISR_BUSY           15
#define I2C_ISR_DIR            16
#define I2C_ISR_ADDCODE        17


#define I2C_ICR_ADDRCF         3
#define I2C_ICR_NACKCF         4
#define I2C_ICR_STOPCF         5
#define I2C_ICR_BERRCF         8
#define I2C_ICR_ARLOCF         9
#define I2C_ICR_OVRCF          10
#define I2C_ICR_PECCF          11
#define I2C_ICR_TIMOUTCF       12
#define I2C_ICR_ALERTCF        13


#define I2C_RXDR_RXDATA        0

#define I2C_TXDR_TXDATA        0





/***************************************************************************************************
 *     BIT POSITIONS DEFINITIONS OF USART PERIPHERAL
 *************************************************************************************************/
#define USART_CR1_UE				0
#define USART_CR1_UESM				1
#define USART_CR1_RE				2
#define USART_CR1_TE				3
#define USART_CR1_IDLEIE			4
#define USART_CR1_RXNEIE			5
#define USART_CR1_TCIE				6
#define USART_CR1_TXEIE				7
#define USART_CR1_PEIE				8
#define USART_CR1_PS				9
#define USART_CR1_PCE				10
#define USART_CR1_WAKE				11
#define USART_CR1_M0				12
#define USART_CR1_MME				13
#define USART_CR1_CMIE				14
#define USART_CR1_OVERS				15
#define USART_CR1_DEDT				16
#define USART_CR1_DEAT				21
#define USART_CR1_RTOIE				26
#define USART_CR1_EOBIE				27
#define USART_CR1_M1				28

#define USART_CR2_ADDM7				4
#define USART_CR2_LBDL				5
#define USART_CR2_LBDIE				6
#define USART_CR2_LBCL				8
#define USART_CR2_CPHA				9
#define USART_CR2_CPOL				10
#define USART_CR2_CKLEN				11
#define USART_CR2_STOP				12
#define USART_CR2_LINEN				14
#define USART_CR2_SWAP				15
#define USART_CR2_RXINV				16
#define USART_CR2_TXINV				17
#define USART_CR2_DATAINV			18
#define USART_CR2_MSBFIRST			19
#define USART_CR2_ABREN				20
#define USART_CR2_ABRMOD			21
#define USART_CR2_RTOEN				23
#define USART_CR2_ADD				24
#define USART_CR2_ADD1				28

#define USART_CR3_EIE				0
#define USART_CR3_IREN				1
#define USART_CR3_IRLP				2
#define USART_CR3_HDSEL				3
#define USART_CR3_NACK				4
#define USART_CR3_SCEN				5
#define USART_CR3_DMAR				6
#define USART_CR3_DMAT				7
#define USART_CR3_RTSE				8
#define USART_CR3_CTSE				9
#define USART_CR3_CTSIE				10
#define USART_CR3_ONEBIT			11
#define USART_CR3_OVRDIS			12
#define USART_CR3_DDRE				13
#define USART_CR3_DEM				14
#define USART_CR3_DEP				15
#define USART_CR3_SCARCNT0			17
#define USART_CR3_SCARCNT1			18
#define USART_CR3_SCARCNT2			19
#define USART_CR3_WUS0				20
#define USART_CR3_WUS1				21
#define USART_CR3_WUFIE				22
#define USART_CR3_UCESM				23
#define USART_CR3_TCBGTIE			24

#define USART_ISR_TC				6
#define USART_ISR_TXE				7
#define USART_ISR_BUSY				16



#endif /* INC_STM32L47XX_H_ */
#include "stm32l475xx_gpio_driver.h"
//#include "stm32l475xx_spi_driver.h"
#include "stm32l47xx_i2c_driver.h"
//#include "stm32l47xx_usart_driver.h"
