#include "baro_service.h"
#include <math.h>

#define BARO_ADDR 0xBA // Dirección del LPS22HB en la placa IoT

HAL_StatusTypeDef Baro_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t data = 0x30; // 0x30 = 25Hz de frecuencia de muestreo, sin filtro adicional

    // Escribimos en el registro CTRL_REG1 (0x10) para encenderlo
    return HAL_I2C_Mem_Write(hi2c, BARO_ADDR, 0x10, 1, &data, 1, 100);
}

void Baro_Update(I2C_HandleTypeDef *hi2c, Baro_Data_t *data) {
	uint8_t raw_press[3];

	    // El registro de presión empieza en 0x28 (PRESS_OUT_L)
	    if (HAL_I2C_Mem_Read(hi2c, BARO_ADDR, 0x28, 1, raw_press, 3, 100) == HAL_OK) {
	        Baro_Process_Data(raw_press, data);
	    }
}

void Baro_Process_Data(uint8_t *raw, Baro_Data_t *data) {
    // Reconstruir el valor de 24 bits
    int32_t press_raw = (int32_t)(raw[2] << 16 | raw[1] << 8 | raw[0]);

    // Convertir a hPa (dividir por 4096 según datasheet)
    data->pressure_hpa = (float)press_raw / 4096.0f;

    // Calcular altitud relativa (Fórmula simplificada)
    // 1013.25 es la presión estándar al nivel del mar
    data->altitude_m = 44330.0f * (1.0f - powf(data->pressure_hpa / 1013.25f, 0.1903f));
}
