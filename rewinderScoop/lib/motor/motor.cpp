#include "motor.hpp"
#include "Arduino.h"

#define MAX_PWM (255)
#define MAX_SPEED (100)

static inline uint32_t clamp(uint32_t input, uint32_t min, uint32_t max)
{
    return (input > max ) ? max : (input < min) ? min : input;
}

static motorPwmFrequency validatePwmFrequency(motorPwmFrequency frequency)
{
    return clamp(frequency, 0, MAX_PWM);
}

static motorPercentage validateMotorPercentage(motorPercentage percentage)
{
    return clamp(percentage, 0, MAX_SPEED);
}

static motorPwmFrequency calculateFrequencyFromPercent(motorPercentage speed)
{
    return map(speed, 0, MAX_SPEED, 0, MAX_PWM);
}

static motorPercentage calculatePercentFromFrequency(motorPwmFrequency freq)
{
    return map(freq, 0, MAX_PWM, 0, MAX_SPEED);
}

static uint32_t calculateSlewRate(motor_t * motor, uint32_t desiredSpeed)
{

    if (desiredSpeed == motor->currentSpeed)
    {
        return desiredSpeed;
    }
    else if (desiredSpeed > motor->currentSpeed)
    {
        desiredSpeed = clamp(desiredSpeed, 0, motor->slewRate * motor->counterMs);
    }
    else
    {
        desiredSpeed = clamp(desiredSpeed, motor->slewRate * motor->counterMs, MAX_SPEED);
    }

    motor->counterMs++;
    return desiredSpeed;
}

void motor__init(motor_t * motor)
{
    
}

void motor__setSpeed(motor_t * motor, uint32_t speed)
{
    speed = validateMotorPercentage(speed);
    motor->requestedSpeed = speed;
    motor->counterMs = 0;
}

void motor__setSpeedInstantly(motor_t * motor, uint32_t speed)
{
    speed = validateMotorPercentage(speed);
    motor->requestedSpeed = speed;
    motor->currentSpeed = speed;
    motor->counterMs = 0;
    analogWrite(motor->pin, calculateFrequencyFromPercent(speed));
}

void motor__setPWMInstantly(motor_t * motor, uint32_t freq)
{
    freq = validatePwmFrequency(freq);
    motor->requestedSpeed = calculatePercentFromFrequency(freq);
    motor->currentSpeed = motor->requestedSpeed;
    motor->counterMs = 0;
    analogWrite(motor->pin, freq);
}

void motor__stop(motor_t * motor)
{
    analogWrite(motor->pin, 0);
    motor->currentSpeed = 0;
    motor->requestedSpeed = 0;
    motor->counterMs = 0;
}

void motor__update(motor_t * motor)
{
    
    motor->currentSpeed = calculateSlewRate(motor, motor->requestedSpeed);
    uint32_t frequency = calculateFrequencyFromPercent(motor->currentSpeed);

    analogWrite(motor->pin, frequency);

}