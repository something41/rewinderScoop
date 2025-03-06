#include "stdint.h"

#define MOTOR_RAMP_TIME_MS (10)
#define MOTOR_MAX_PWM (255)

typedef uint32_t motorPercentage;
typedef uint32_t motorPwmFrequency;

typedef struct
{
    const uint32_t pin;
    uint32_t currentSpeed;
    uint32_t requestedSpeed;
    uint32_t counterMs;
    const uint32_t slewRate;
} motor_t;


#define MOTOR_INIT(_PIN, _SLEW_RATE) \
{ \
    .pin = _PIN,    \
    .currentSpeed = 0, \
    .requestedSpeed = 0, \
    .counterMs = 0, \
    .slewRate = _SLEW_RATE, \
}

void motor__stop(motor_t * motor);

void motor__update(motor_t * motor);

void motor__setSpeed(motor_t * motor, uint32_t speed);

void motor__setSpeedInstantly(motor_t * motor, uint32_t speed);

void motor__setPWMInstantly(motor_t * motor, uint32_t freq);

void motor__init(motor_t * motor);