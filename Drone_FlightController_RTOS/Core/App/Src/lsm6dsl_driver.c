#include "main.h"

#define LSM6DSL_ADDR 0xD4
#define LSM6DSL_WHO_AM_I 0x0F
#define LSM6DSL_CTRL1_XL  0x10
#define LSM6DSL_CTRL2_G   0x11
#define LSM6DSL_OUTX_L_G  0x22 // Inicio de los 12 bytes de datos (Gyro + Accel)

// Inicializa el hardware del sensor
HAL_StatusTypeDef LSM6DSL_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t check;
    HAL_I2C_Mem_Read(hi2c, LSM6DSL_ADDR, LSM6DSL_WHO_AM_I, 1, &check, 1, 100);
    if (check != 0x6A) return HAL_ERROR;

    // Config: 104Hz, +/- 4g para Accel y 500 dps para Gyro
    uint8_t config[] = {0x48, 0x44};
    HAL_I2C_Mem_Write(hi2c, LSM6DSL_ADDR, LSM6DSL_CTRL1_XL, 1, &config[0], 1, 100);
    HAL_I2C_Mem_Write(hi2c, LSM6DSL_ADDR, LSM6DSL_CTRL2_G, 1, &config[1], 1, 100);

    return HAL_OK;
}

// Dispara la lectura por DMA
void LSM6DSL_ReadRaw_DMA(I2C_HandleTypeDef *hi2c, uint8_t *buffer) {
    HAL_I2C_Mem_Read_DMA(hi2c, LSM6DSL_ADDR, LSM6DSL_OUTX_L_G, 1, buffer, 12);
}
