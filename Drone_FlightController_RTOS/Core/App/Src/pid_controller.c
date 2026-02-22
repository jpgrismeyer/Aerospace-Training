#include "pid_controller.h"

void PID_Init(PID_Instance_t *pid, float p, float i, float d, float min, float max) {
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    pid->out_min = min;
    pid->out_max = max;
    pid->integral = 0.0f;
    pid->last_error = 0.0f;
}

float PID_Compute(PID_Instance_t *pid, float target, float measured, float dt) {
    // 1. Calcular error
    float error = target - measured;

    // 2. Proporcional
    float p_term = pid->kp * error;

    // 3. Integral con Anti-Windup simple
    pid->integral += error * dt;
    float i_term = pid->ki * pid->integral;

    // Limitar la integral para evitar saturación (Clamping)
    if (i_term > pid->out_max) i_term = pid->out_max;
    if (i_term < pid->out_min) i_term = pid->out_min;

    // 4. Derivativo (Basado en el cambio del error)
    float d_term = pid->kd * ((error - pid->last_error) / dt);

    // 5. Resultado total
    pid->output = p_term + i_term + d_term;

    // 6. Saturación de salida total
    if (pid->output > pid->out_max) pid->output = pid->out_max;
    if (pid->output < pid->out_min) pid->output = pid->out_min;

    // Guardar error para la próxima vez
    pid->last_error = error;

    return pid->output;
}

void PID_Reset(PID_Instance_t *pid) {
    pid->integral = 0.0f;
    pid->last_error = 0.0f;
    pid->output = 0.0f;
}
