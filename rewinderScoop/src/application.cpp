#include <Arduino.h>
#include "configuration.hpp"

#include "system.hpp"
#include "motor.hpp"
#include "rotaryEncoder.hpp"
#include "stopLight.hpp"
#include "sevenSegmentDisplay.hpp"
#include "button.hpp"





static systemState_t setupState();
static systemState_t startState();
static systemState_t runningState();
static systemState_t finishState();

void update();


systemState_t currentState = SYSTEM_STATE_SETUP;
motor_t motorObj = MOTOR_INIT(PIN_MOTOR, 10);
motor_t * motor = &motorObj;

rotaryEncoder encoderObj = ROTARY_ENCODER_INIT(PIN_ENCODER_A, PIN_ENCODER_B, 1);
rotaryEncoder * encoder = &encoderObj;

stopLight_t stopLightObj = STOPLIGHT_INIT(PIN_LED_RED, PIN_LED_YELLOW, PIN_LED_GREEN);
stopLight_t * stopLight = &stopLightObj;

sevenSegmentDisplay_t ssdObj = SEVEN_SEGMENT_DISPLAY_INIT(DEFAULT_I2C_ADDRESS);
sevenSegmentDisplay_t * ssd = &ssdObj;

button_t buttonObj = BUTTON_INIT(PIN_BUTTON);
button_t * button = &buttonObj;

void setup()
{
	Serial.begin(115200);
	pinMode(D0, INPUT_PULLUP);
	sevenSegmentDisplay__init(ssd);
}

void loop()
{
	uint32_t currentMillis = millis();


	//First update all processes
	update();

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
	if (button__getStatus(button))
	{

		return SYSTEM_STATE_START;
	}
	return SYSTEM_STATE_SETUP;
}

systemState_t startState()
{
	rotaryEncoder__reset(encoder);
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

void update()
{
	//motor__update(motor);
	//motor__setPWMInstantly(motor, 100);
	motor__setSpeed(motor, 0);

	rotaryEncoder__update(encoder);
	sevenSegmentDisplay__update(ssd);
	stopLight__update(stopLight);
	button__update(button);
}
