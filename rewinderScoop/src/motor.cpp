#include "motor.hpp"
#include "Arduino.h"



void motor__rampUp(motor_t * motor)
{
    analogWrite(motor->pin, motor->rampUpScale * MOTOR_MAX_PWM  * motor->counterMs);
    motor->counterMs++;
}

void motor__rampDown(motor_t * motor)
{
    analogWrite(motor->pin, motor->rampDownScale * MOTOR_MAX_PWM  * motor->counterMs);
    motor->counterMs++;
}

void motor__setSpeed(motor_t * motor, uint32_t speed)
{
    analogWrite(motor->pin, speed);
}

void motor__setState(motor_t * motor, motorState_t state)
{
    motor->state = state;
}

void motor__stop(motor_t * motor)
{
    analogWrite(motor->pin, 0);
}