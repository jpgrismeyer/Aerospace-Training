#ifndef MOTOR_MIXER_H
#define MOTOR_MIXER_H

#include "main.h"

// Definimos los límites del ESC (1ms a 2ms)
#define MOTOR_MIN_PULSE 1000
#define MOTOR_MAX_PULSE 2000
#define MOTOR_IDLE      1100  // Potencia mínima para que giren apenas armados

void Mixer_Init(TIM_HandleTypeDef *htim);
void Mixer_Update(float throttle, float pitch, float roll, float yaw);

#endif
