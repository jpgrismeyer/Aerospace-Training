#include "imu_service.h"
#include <math.h>

// Definiciones necesarias para que la matemática funcione
#define ALPHA 0.98f
#define LSM6DSL_ADDR 0xD4

// 1. FUNCIÓN DE INICIALIZACIÓN: Despierta al sensor
HAL_StatusTypeDef IMU_Init_Service(I2C_HandleTypeDef *hi2c) {
    uint8_t data;

    // Configurar Acelerómetro: 104Hz, +/- 4g
    data = 0x48;
    HAL_I2C_Mem_Write(hi2c, LSM6DSL_ADDR, 0x10, 1, &data, 1, 100);

    // Configurar Giroscopio: 104Hz, 500 dps
    data = 0x44;
    return HAL_I2C_Mem_Write(hi2c, LSM6DSL_ADDR, 0x11, 1, &data, 1, 100);
}

// 2. FUNCIÓN DE ACTUALIZACIÓN: La que llamás desde el Main
void IMU_Update(I2C_HandleTypeDef *hi2c, IMU_Data_t *data, float dt) {
    uint8_t buffer[12];

    // Leemos 12 bytes desde el registro 0x22 (Gyro + Accel)
    if (HAL_I2C_Mem_Read(hi2c, LSM6DSL_ADDR, 0x22, 1, buffer, 12, 100) == HAL_OK) {
        // Llamamos a tu función de procesamiento
        IMU_Process_Data(buffer, data, dt);
    }
}

// 3. TU FUNCIÓN DE PROCESAMIENTO: La lógica matemática
void IMU_Process_Data(uint8_t *raw, IMU_Data_t *data, float dt) {
    // Reconstrucción de bytes
    int16_t g_x = (int16_t)(raw[1] << 8 | raw[0]);
    int16_t g_y = (int16_t)(raw[3] << 8 | raw[2]);
    int16_t a_x = (int16_t)(raw[7] << 8 | raw[6]);
    int16_t a_y = (int16_t)(raw[9] << 8 | raw[8]);
    int16_t a_z = (int16_t)(raw[11] << 8 | raw[10]);

    // Escalado
    data->gyro_x = g_x * 0.0175f;
    data->gyro_y = g_y * 0.0175f;

    // Acelerómetro (Ángulos)
    float acc_pitch = atan2f((float)a_x, (float)a_z) * 57.2958f;
    float acc_roll  = atan2f((float)a_y, (float)a_z) * 57.2958f;

    // Filtro Complementario
    data->pitch = ALPHA * (data->pitch + data->gyro_x * dt) + (1.0f - ALPHA) * acc_pitch;
    data->roll  = ALPHA * (data->roll  + data->gyro_y * dt) + (1.0f - ALPHA) * acc_roll;
}
