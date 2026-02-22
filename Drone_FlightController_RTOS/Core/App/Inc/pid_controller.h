#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <stdint.h>

typedef struct {
    // Coeficientes (Se ajustan en el tuning)
    float kp;
    float ki;
    float kd;

    // Estado interno
    float setpoint;
    float integral;
    float last_error;

    // Límites de seguridad
    float out_max;
    float out_min;

    // Resultado
    float output;
} PID_Instance_t;

// Prototipos de funciones
void PID_Init(PID_Instance_t *pid, float p, float i, float d, float min, float max);
float PID_Compute(PID_Instance_t *pid, float target, float measured, float dt);
void PID_Reset(PID_Instance_t *pid);

#endif
