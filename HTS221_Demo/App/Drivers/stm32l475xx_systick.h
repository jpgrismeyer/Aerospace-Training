/*
 * stm32l475xx_systick.h
 *
 *  Created on: May 23, 2025
 *      Author: admin
 */

#ifndef INC_STM32L475XX_SYSTICK_H_
#define INC_STM32L475XX_SYSTICK_H_

#include <stdint.h>

void systick_init(uint32_t reload_val);
void delay_ms(uint32_t ms);

#endif /* INC_STM32L475XX_SYSTICK_H_ */
