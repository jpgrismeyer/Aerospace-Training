#include "motor_mixer.h"

static TIM_HandleTypeDef *motor_timer;

void Mixer_Init(TIM_HandleTypeDef *htim) {
    motor_timer = htim;
}

void Mixer_Update(float throttle, float pitch, float roll, float yaw) {
    // Fórmulas de mezcla para configuración en X
    // Motor 1: Front Right (CCW)
    // Motor 2: Front Left  (CW)
    // Motor 3: Rear Right  (CW)
    // Motor 4: Rear Left   (CCW)

    float m1 = throttle - pitch - roll + yaw;
    float m2 = throttle - pitch + roll - yaw;
    float m3 = throttle + pitch - roll - yaw;
    float m4 = throttle + pitch + roll + yaw;

    float motors[4] = {m1, m2, m3, m4};

    for (int i = 0; i < 4; i++) {
        // 1. Clamping: Evitar que los valores se salgan del rango 1000-2000
        if (motors[i] > MOTOR_MAX_PULSE) motors[i] = MOTOR_MAX_PULSE;
        if (motors[i] < MOTOR_MIN_PULSE) motors[i] = MOTOR_MIN_PULSE;

        // Si el throttle es muy bajo (motores desarmados), forzamos a 1000
        if (throttle < MOTOR_IDLE) motors[i] = MOTOR_MIN_PULSE;
    }

    // 2. Escribir en los registros del Timer (PWM)
    __HAL_TIM_SET_COMPARE(motor_timer, TIM_CHANNEL_1, (uint32_t)motors[0]);
    __HAL_TIM_SET_COMPARE(motor_timer, TIM_CHANNEL_2, (uint32_t)motors[1]);
    __HAL_TIM_SET_COMPARE(motor_timer, TIM_CHANNEL_3, (uint32_t)motors[2]);
    __HAL_TIM_SET_COMPARE(motor_timer, TIM_CHANNEL_4, (uint32_t)motors[3]);
}
