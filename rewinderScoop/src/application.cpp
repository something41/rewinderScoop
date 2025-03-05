#include <Arduino.h>

#include "configuration.hpp"
#include "application.hpp"

#include "motor.hpp"
#include "rotaryEncoder.hpp"
#include "stopLight.hpp"
#include "sevenSegmentDisplay.hpp"
#include "button.hpp"

job_t testJob = CREATE_JOB(100, 25);

systemState_t currentState = SYSTEM_STATE_SETUP;
motor_t motorObj = MOTOR_INIT(PIN_MOTOR, 10);
motor_t * motor = &motorObj;

rotaryEncoder_t encoderObj = ROTARY_ENCODER_INIT(PIN_ENCODER_A, PIN_ENCODER_B, 1);
rotaryEncoder_t * encoder = &encoderObj;

stopLight_t stopLightObj = STOPLIGHT_INIT(PIN_LED_RED, PIN_LED_YELLOW, PIN_LED_GREEN);
stopLight_t * stopLight = &stopLightObj;

sevenSegmentDisplay_t sevenSegmentDisplayObj = SEVEN_SEGMENT_DISPLAY_INIT(DEFAULT_I2C_ADDRESS);
sevenSegmentDisplay_t * sevenSegmentDisplay = &sevenSegmentDisplayObj;

button_t buttonObj = BUTTON_INIT(PIN_BUTTON);
button_t * button = &buttonObj;

void setup()
{
	Serial.begin(115200);
	pinMode(D0, INPUT_PULLUP);
	system__init();

}

void loop()
{
	uint32_t currentMillis = millis();

	//First update all processes
	system__update();

	systemState_t nextState = currentState;

	switch(currentState)
	{
	case SYSTEM_STATE_SETUP:
		nextState = setupState();
		break;
	case SYSTEM_STATE_START:
		nextState = startState();
		//fall through
	case SYSTEM_STATE_TRANISITION_TO_RUN_0:
		nextState = transitionToRun0State();
		break;
	case SYSTEM_STATE_RUN_0:
		nextState = run0State();
		break;
	case SYSTEM_STATE_TRANISITION_TO_RUN_1:
		nextState = transitionToRun1State();
		break;
	case SYSTEM_STATE_RUN_1:
		nextState = run1State();
		break;
	case SYSTEM_STATE_FINISH:
		nextState = finishState();
		break;
	case SYSTEM_STATE_ERROR:
		nextState = errorState();
	}

	waitForNextMs(currentMillis);

}

systemState_t setupState()
{

	// display job choice on ssd


	if (button__getStatus(button))
	{
		return SYSTEM_STATE_START;
	}
	return SYSTEM_STATE_SETUP;
}

systemState_t startState()
{
	rotaryEncoder__reset(encoder);
	return SYSTEM_STATE_TRANISITION_TO_RUN_0;
}

systemState_t finishState()
{
	motor__stop(motor);
	return SYSTEM_STATE_SETUP;
}

systemState_t run0State()
{
	bool errorDetected = rotaryEncoder__stallErrorDetected(encoder);

	if (errorDetected)
	{
		return SYSTEM_STATE_ERROR;
	}

	uint32_t feetPulled = rotaryEncoder__getScaledValue(encoder);

	sevenSegementDisplay__displayValue(sevenSegmentDisplay, feetPulled);

	return feetPulled >= testJob.runs[0].distanceInFeet ? SYSTEM_STATE_TRANISITION_TO_RUN_1 : SYSTEM_STATE_RUN_0;
}

systemState_t run1State()
{
	return SYSTEM_STATE_RUN_1;
}

systemState_t transitionToRun0State()
{
	motor__setSpeed(motor, testJob.runs[0].percentSpeed);

	return SYSTEM_STATE_RUN_0;
}

systemState_t transitionToRun1State()
{
	return SYSTEM_STATE_RUN_1;
}

systemState_t errorState()
{

}

void system__update()
{
	//motor__update(motor);
	//motor__setPWMInstantly(motor, 100);
	motor__setSpeed(motor, 0);

	rotaryEncoder__update(encoder);
	sevenSegmentDisplay__update(sevenSegmentDisplay);
	stopLight__update(stopLight);
	button__update(button);
}


void system__init()
{
	sevenSegmentDisplay__init(sevenSegmentDisplay);
	motor__init(motor);
	stopLight__init(stopLight);
	button__init(button);
	rotaryEncoder__init(encoder);
}

void waitForNextMs(uint32_t currentMs)
{
	while (millis() - currentMs < ONE_MS)
	{

	}
}