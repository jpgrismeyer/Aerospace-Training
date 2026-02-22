#ifndef BARO_SERVICE_H
#define BARO_SERVICE_H

#include "main.h"

// Estructura para los datos del barómetro
typedef struct {
    float pressure_hpa;    // Presión en hectopascales
    float altitude_m;      // Altitud calculada en metros
    float temperature_c;   // Por si después queremos compensar por temperatura
} Baro_Data_t;

// Prototipos de funciones (exactamente como las definimos en el .c)
HAL_StatusTypeDef Baro_Init(I2C_HandleTypeDef *hi2c);
void Baro_Update(I2C_HandleTypeDef *hi2c, Baro_Data_t *data);
void Baro_Process_Data(uint8_t *raw, Baro_Data_t *data);

#endif
