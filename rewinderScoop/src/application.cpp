#include <Arduino.h>

#include "application.hpp"

#include "motor.hpp"
#include "rotaryEncoder.hpp"
#include "stopLight.hpp"
#include "sevenSegmentDisplay.hpp"
#include "button.hpp"

system_t rewinder = SYSTEM_INIT();

motor_t motorObj = MOTOR_INIT(PIN_MOTOR, 10);
motor_t * motor = &motorObj;

rotaryEncoder_t encoderObj = ROTARY_ENCODER_INIT(PIN_ENCODER_A, PIN_ENCODER_B, 1);
rotaryEncoder_t * encoder = &encoderObj;

stopLight_t stopLightObj = STOPLIGHT_INIT(PIN_LED_RED, PIN_LED_YELLOW, PIN_LED_GREEN);
stopLight_t * stopLight = &stopLightObj;

sevenSegmentDisplay_t sevenSegmentDisplayObj = SEVEN_SEGMENT_DISPLAY_INIT(DEFAULT_I2C_ADDRESS);
sevenSegmentDisplay_t * sevenSegmentDisplay = &sevenSegmentDisplayObj;

button_t buttonObj = BUTTON_INIT(PIN_BUTTON);
button_t * goButton = &buttonObj;

static inline uint32_t getCurrentRunDistance()
{
	return rewinder.jobSelections[rewinder.jobIndex].runs[rewinder.runIndex].distanceInFeet;
}

static inline motorPercentage getCurrentRunSpeed()
{
	return rewinder.jobSelections[rewinder.jobIndex].runs[rewinder.runIndex].percentSpeed;
}

static inline uint32_t getCurrentJobDistance()
{
	return rewinder.jobSelections[rewinder.jobIndex].runs[0].distanceInFeet + rewinder.jobSelections[rewinder.jobIndex].runs[1].distanceInFeet;
}

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

	sevenSegmentDisplay__displayError(sevenSegmentDisplay);
/*
	systemState_t nextState = rewinder.currentState;

	switch(rewinder.currentState)
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
	case SYSTEM_STATE_RUN_0:p
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

	rewinder.currentState = nextState;
*/
	waitForNextMs(currentMillis);

}

systemState_t setupState()
{

	// display job choice on ssd
	uint32_t jobLength = getCurrentJobDistance();

	stopLight__setRed(stopLight);

	sevenSegementDisplay__displayValue(sevenSegmentDisplay, jobLength);

	if (button__getStatus(goButton))
	{
		return SYSTEM_STATE_START;
	}
	return SYSTEM_STATE_SETUP;
}

systemState_t startState()
{
	rotaryEncoder__reset(encoder);
	stopLight__setGreen(stopLight);

	rewinder.runIndex = 0;
	
	return SYSTEM_STATE_TRANISITION_TO_RUN;
}

systemState_t runState()
{
	bool errorDetected = rotaryEncoder__stallErrorDetected(encoder);

	if (errorDetected)
	{
		return SYSTEM_STATE_ERROR;
	}

	uint32_t feetPulled = rotaryEncoder__getScaledValue(encoder);

	sevenSegementDisplay__displayValue(sevenSegmentDisplay, feetPulled);

	if (feetPulled >= getCurrentRunDistance())
	{
		// Hooray! We finished a run
		rewinder.runIndex++;
	}

	return rewinder.runIndex >= 2 ? SYSTEM_STATE_TRANISITION_TO_RUN : SYSTEM_STATE_RUN;
}

systemState_t transitionToRunState()
{
	motor__setSpeed(motor, getCurrentRunSpeed());

	if (rewinder.runIndex == 0)
	{
		stopLight__setGreen(stopLight);
	}
	else
	{
		//assume its index 1
		stopLight__setYellow(stopLight);
	}

	return SYSTEM_STATE_RUN;
}


systemState_t finishState()
{
	motor__stop(motor);
	stopLight__setRed(stopLight);

	return SYSTEM_STATE_SETUP;
}

systemState_t errorState()
{
	// something went wrong display error
	// stay in here forever until device gets rebooted
	motor__stop(motor);
	sevenSegmentDisplay__displayError(sevenSegmentDisplay);
	stopLight__error(stopLight);
	return SYSTEM_STATE_ERROR;
}

void system__update()
{
	motor__update(motor);
	rotaryEncoder__update(encoder);
	sevenSegmentDisplay__update(sevenSegmentDisplay);
	stopLight__update(stopLight);
	button__update(goButton);

}


void system__init()
{
	sevenSegmentDisplay__init(sevenSegmentDisplay);
	motor__init(motor);
	stopLight__init(stopLight);
	button__init(goButton);
	rotaryEncoder__init(encoder);

}

void waitForNextMs(uint32_t currentMs)
{
	while (millis() - currentMs < ONE_MS){}
}
