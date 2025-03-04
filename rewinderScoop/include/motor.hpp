#include "stdint.h"

#define MOTOR_RAMP_TIME_MS (10)
#define MOTOR_MAX_PWM (255)

typedef enum
{
    MOTOR_STATE_IDLE = 0,
    MOTOR_STATE_RAMPING_UP,
    MOTOR_STATE_FULL_SPEED,
    MOTOR_STATE_RAMPING_DOWN_1,
    MOTOR_STATE_SLOW_SPEED,
    RMOTOR_STATE_AMPING_DOWN_2
} motorState_t;

typedef struct
{
    const uint32_t pin;
    motorState_t state;
    uint32_t counterMs;
    const uint32_t rampUpScale;
    const uint32_t rampDownScale;
} motor_t;


#define MOTOR_INIT(_PIN, _RAMP_UP_SCALE, _RAMP_DOWN_SCALE) { \
    .pin = _PIN,    \
    .state = MOTOR_STATE_IDLE,  \
    .counterMs = 0, \
    .rampUpScale = _RAMP_UP_SCALE, \
    .rampDownScale = _RAMP_DOWN_SCALE, \
}


void motor__rampUp(motor_t * motor);

void motor__rampDown(motor_t * motor);

void motor__setState(motor_t * motor, motorState_t state);

void motor__stop(motor_t * motor);