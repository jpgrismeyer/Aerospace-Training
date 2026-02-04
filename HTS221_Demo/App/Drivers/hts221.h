#ifndef HTS221_H
#define HTS221_H

#include <stdint.h>
#include <stdbool.h>

/* Dirección I2C 7-bit del HTS221 según datasheet */
#define HTS221_ADDR_7BIT        0x5F

/* Registros importantes */
#define HTS221_REG_WHO_AM_I     0x0F
#define HTS221_WHO_AM_I_VAL     0xBC

#define HTS221_REG_CTRL1        0x20
/* bits en CTRL1:
   PD (bit7) = 1 encender
   BDU (bit2)= 1 block update
   ODR1:0 (1:0) = 01 -> 1 Hz, por ejemplo
*/

/* API */
bool HTS221_Init(void);
bool HTS221_ReadWhoAmI(uint8_t *out_val);

float HTS221_ReadTemperatureC(void);
float HTS221_ReadHumidityPerc(void);

#endif
