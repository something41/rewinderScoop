#include "stdint.h"

#define MOTOR_RAMP_TIME_MS (10)
#define MOTOR_MAX_PWM (255)

typedef uint32_t motorPercentage;
typedef uint32_t motorPwmFrequency;

typedef enum
{
    MOTOR_STATE_IDLE = 0,
    MOTOR_STATE_RAMPING_UP,
    MOTOR_STATE_FULL_SPEED,
    MOTOR_STATE_RAMPING_DOWN_1,
    MOTOR_STATE_SLOW_SPEED,
    MOTOR_STATE_RAMPING_DOWN_2
} motorState_t;

typedef struct
{
    const uint32_t pin;
    motorState_t state;
    uint32_t currentSpeed;
    uint32_t requestedSpeed;
    uint32_t counterMs;
    const uint32_t slewRate;
} motor_t;


#define MOTOR_INIT(_PIN, _SLEW_RATE) \
{ \
    .pin = _PIN,    \
    .state = MOTOR_STATE_IDLE,  \
    .currentSpeed = 0, \
    .requestedSpeed = 0, \
    .counterMs = 0, \
    .slewRate = _SLEW_RATE, \
}

void motor__setState(motor_t * motor, motorState_t state);

void motor__stop(motor_t * motor);

void motor__update(motor_t * motor);

void motor__setSpeed(motor_t * motor, uint32_t speed);

void motor__setSpeedInstantly(motor_t * motor, uint32_t speed);

void motor__setPWMInstantly(motor_t * motor, uint32_t freq);