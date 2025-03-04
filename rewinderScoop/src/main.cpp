#include <Arduino.h>
#include <Encoder.h>
#include <Wire.h>
#include "system.hpp"
#include "motor.hpp"
#include "rotaryEncoder.hpp"
#include "stopLight.hpp"

#define PIN_BUTTON     (D0)
#define PIN_I2C_SCL    (D1)
#define PIN_I2C_SCA    (D2)
#define PIN_LED_RED    (D3)
#define PIN_LED_YELLOW (D4)
#define PIN_LED_GREEN  (D5)
#define PIN_ENCODER_A  (D6)
#define PIN_ENCODER_B  (D7)
#define PIN_MOTOR      (D8)


static systemState_t setupState();
static systemState_t startState();
static systemState_t runningState();
static systemState_t finishState();


systemState_t currentState = SYSTEM_STATE_SETUP;
motor_t motorObj = MOTOR_INIT(PIN_MOTOR, MOTOR_MAX_PWM / MOTOR_RAMP_TIME_MS, MOTOR_MAX_PWM / MOTOR_RAMP_TIME_MS);
motor_t * motor = &motorObj;

rotaryEncoder encoderObj = ROTARY_ENCODER_INIT(PIN_ENCODER_A, PIN_ENCODER_B, 1);
rotaryEncoder * encoder = & encoderObj;

stopLight_t stopLightObj = STOPLIGHT_INIT(PIN_LED_RED, PIN_LED_YELLOW, PIN_LED_GREEN);

void setup()
{
	Serial.begin(115200);
	pinMode(D0, INPUT_PULLUP);
}

void loop()
{
	uint32_t currentMillis = millis();

	switch(currentState)
	{
	case SYSTEM_STATE_SETUP:
		setupState();
		break;
	case SYSTEM_STATE_START:
		startState();
		//fall through
	case SYSTEM_STATE_RUNNING:
		runningState();
		break;
	case SYSTEM_STATE_FINISH:
		finishState();
		break;
	}


	while (millis() - currentMillis < ONE_MS)
	{

	}
}

systemState_t setupState()
{
	return digitalRead(PIN_BUTTON) ? SYSTEM_STATE_START : SYSTEM_STATE_SETUP;
}

systemState_t startState()
{
	//rotaryEncoder.write(0);
	motor__setState(motor, MOTOR_STATE_RAMPING_UP);
	return SYSTEM_STATE_RUNNING;
}

systemState_t runningState()
{
	return SYSTEM_STATE_RUNNING;
}

systemState_t finishState()
{
	return SYSTEM_STATE_FINISH;
}


