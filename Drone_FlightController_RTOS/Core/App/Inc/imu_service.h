#ifndef IMU_SERVICE_H
#define IMU_SERVICE_H

#include "main.h"

typedef struct {
    float pitch;    // Ángulo filtrado
    float roll;     // Ángulo filtrado
    float gyro_x;   // Velocidad angular actual
    float gyro_y;
} IMU_Data_t;

typedef struct {
    float throttle_cmd;
    float pitch_cmd;
    float roll_cmd;
    float yaw_cmd;
} Control_Cmd_t;
HAL_StatusTypeDef IMU_Init_Service(I2C_HandleTypeDef *hi2c);
void IMU_Update(I2C_HandleTypeDef *hi2c, IMU_Data_t *data, float dt);
void IMU_Process_Data(uint8_t *raw, IMU_Data_t *data, float dt);
#endif
