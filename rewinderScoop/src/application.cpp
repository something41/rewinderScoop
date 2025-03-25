#include <Arduino.h>

#include "application.hpp"

#include "motor.hpp"

#include "ledDisplay.hpp"
#include "sevenSegmentDisplay.hpp"
#include "button.hpp"
#include "knob.hpp"
#include "dial.hpp"
#include "zCounter.hpp"

#include "rotaryEncoder.hpp"

system_t rewinder = SYSTEM_INIT();

motor_t motorObj = MOTOR_INIT(PIN_MOTOR, MOTOR_RAMP_TIME_MS);
motor_t * motor = &motorObj;

rotaryEncoder_t encoderObj = ROTARY_ENCODER_INIT(PIN_ENCODER_A, PIN_ENCODER_Z, ENCODER_SCALE_MULTIPLIER, ENCODER_SCALE_DIVIDER, ENCODER_A_PULSES_PER_REVOLUTION, ENCODER_A_TIME_OUT_MS, ENCODER_FINISH_TIME_OUT_MS);
rotaryEncoder_t * encoder = &encoderObj;

ledDisplay_t stopLightObj = LED_DISPLAY_INIT(PIN_LED_RED, PIN_LED_YELLOW, PIN_LED_GREEN);
ledDisplay_t * stopLight = &stopLightObj;

sevenSegmentDisplay_t sevenSegmentDisplayObj = SEVEN_SEGMENT_DISPLAY_INIT(DEFAULT_I2C_ADDRESS, 100);
sevenSegmentDisplay_t * sevenSegmentDisplay = &sevenSegmentDisplayObj;

button_t startButtonObj = BUTTON_INIT(PIN_START_BUTTON);
button_t * startButton = &startButtonObj;

knob_t knobObj = KNOB_INIT(PIN_KNOB);
knob_t * knob = &knobObj;

dial_t customDistanceDialObj = DIAL_INIT(PIN_DIAL, CUSTOM_DISTANCE_MIN, CUSTOM_DISTANCE_MAX);
dial_t * customDistanceDial = &customDistanceDialObj;


uint32_t debugCounter = 0;
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
	return rewinder.jobSelections[rewinder.jobIndex].runs[1].distanceInFeet;
}

static void setCustomDistance(uint32_t value)
{
	rewinder.jobSelections[CUSTOM_JOB_INDEX].runs[0].distanceInFeet = CUSTOM_PERCENT_FAST * value;
	rewinder.jobSelections[CUSTOM_JOB_INDEX].runs[1].distanceInFeet = value;
}

static void printStateTransition()
{
	if (rewinder.currentState != rewinder.previousState)
	{
		switch (rewinder.currentState)
		{
			case SYSTEM_STATE_SETUP:
				Serial.println("SYSTEM_STATE_SETUP");
				break;
			case SYSTEM_STATE_START:
				Serial.println("SYSTEM_STATE_START");
				break;
			case SYSTEM_STATE_TRANSITION_TO_RUN:
				Serial.println("SYSTEM_STATE_TRANSITION_TO_RUN");
				break;
			case SYSTEM_STATE_RUN:
				Serial.println("SYSTEM_STATE_RUN");
				break;
			case SYSTEM_STATE_FINISH:
				Serial.println("SYSTEM_STATE_FINISH");
				break;
			case SYSTEM_STATE_ERROR:
				Serial.println("SYSTEM_STATE_ERROR");
				break;
			case SYSTEM_STATE_WAIT_UNTIL_NO_MOVEMENT:
				Serial.println("SYSTEM_STATE_WAIT_UNTIL_NO_MOVEMENT");
				break;
			default:
				break;
		}
	}

	rewinder.previousState = rewinder.currentState;
}

void setup()
{
#if (ENABLE_DEBUG)
	Serial.begin(115200);
#endif
	system__init();
#if (ENABLE_DEBUG)
	Serial.println("init complete.");
#endif
}

void loop()
{
	uint32_t currentMillis = millis();

	//First update all processes
	system__update();

	systemState_t nextState = rewinder.currentState;

	switch(rewinder.currentState)
	{
		case SYSTEM_STATE_SETUP:
			nextState = setupState();
			break;
		case SYSTEM_STATE_START:
			nextState = startState();
			break;
		case SYSTEM_STATE_TRANSITION_TO_RUN:
			nextState = transitionToRunState();
			break;
		case SYSTEM_STATE_RUN:
			nextState = runState();
			break;
		case SYSTEM_STATE_FINISH:
			nextState = finishState();
			break;
		case SYSTEM_STATE_WAIT_UNTIL_NO_MOVEMENT:
			nextState = waitForNoMovementState();
			break;
		case SYSTEM_STATE_ERROR:
			nextState = errorState();
			break;
		default:
			break;
	}

	rewinder.currentState = nextState;
#if (ENABLE_DEBUG)
	printStateTransition();
#endif

	waitForNextMs(currentMillis);

}

systemState_t setupState()
{

	uint32_t selection = knob__getSelection(knob);

	if (selection == KNOB_NUM_VALUES)
	{
		// custom mode enabled
		uint32_t customDistance  = dial__getReading(customDistanceDial);
		setCustomDistance(customDistance);
		rewinder.jobIndex = CUSTOM_JOB_INDEX;
	}
	else
	{
		rewinder.jobIndex = knob__getSelection(knob);
	}

	//Serial.println(selection);

	uint32_t jobLength = getCurrentJobDistance();

	ledDisplay__setStop(stopLight);

	sevenSegmentDisplay__displayValue(sevenSegmentDisplay, jobLength);

	if (button__getStatus(startButton) == true)
	{
		return SYSTEM_STATE_START;
	}
	return SYSTEM_STATE_SETUP;
}

systemState_t startState()
{
	rotaryEncoder__reset(encoder);

	rewinder.runIndex = 0;

	return SYSTEM_STATE_TRANSITION_TO_RUN;
}

systemState_t transitionToRunState()
{
	motor__setSpeed(motor, getCurrentRunSpeed());

	if (rewinder.runIndex == 0)
	{
		ledDisplay__setFast(stopLight);
	}
	else
	{
		//assume its index 1
		ledDisplay__setSlow(stopLight);
	}

	return SYSTEM_STATE_RUN;
}

systemState_t runState()
{
	bool errorDetected = 0; //rotaryEncoder__stallErrorDetected(encoder);

	if (errorDetected)
	{
		return SYSTEM_STATE_ERROR;
	}

	uint32_t inchesPulled = rotaryEncoder__getScaledValue(encoder);

	sevenSegmentDisplay__displayValue(sevenSegmentDisplay, inchesPulled);

	if (inchesPulled >= getCurrentRunDistance())
	{
		// Hooray! We finished a run
		rewinder.runIndex++;

		return rewinder.runIndex >= 2 ? SYSTEM_STATE_FINISH : SYSTEM_STATE_TRANSITION_TO_RUN;
	}

	return SYSTEM_STATE_RUN;
}

systemState_t waitForNoMovementState()
{
	uint32_t inchesPulled = rotaryEncoder__getScaledValue(encoder);

	sevenSegmentDisplay__displayValue(sevenSegmentDisplay, inchesPulled);

	return rotaryEncoder__isFinished(encoder) ? SYSTEM_STATE_SETUP : SYSTEM_STATE_WAIT_UNTIL_NO_MOVEMENT;

}

systemState_t finishState()
{
	motor__stop(motor);
	ledDisplay__setStop(stopLight);

	rotaryEncoder__enterFinishMode(encoder);

	return SYSTEM_STATE_WAIT_UNTIL_NO_MOVEMENT;
}

systemState_t errorState()
{
	// something went wrong display error
	// stay in here forever until device gets rebooted
	motor__stop(motor);
	sevenSegmentDisplay__displayError(sevenSegmentDisplay);
	ledDisplay__setError(stopLight);
	return SYSTEM_STATE_ERROR;
}

void system__update()
{
	knob__update(knob); //should be updated before displays and buttons
	motor__update(motor);
	rotaryEncoder__update(encoder);
	sevenSegmentDisplay__update(sevenSegmentDisplay);
	ledDisplay__update(stopLight);
	button__update(startButton);
	dial__update(customDistanceDial);						
}

void system__init()
{
	//analogReadResolution(14);

	sevenSegmentDisplay__init(sevenSegmentDisplay);
	motor__init(motor);
	ledDisplay__init(stopLight);
	button__init(startButton);
	knob__init(knob);
	dial__init(customDistanceDial);
	rotaryEncoder__init(encoder);
	rotaryEncoder__enterRunMode(encoder);

}

void waitForNextMs(uint32_t currentMs)
{
	while (millis() - currentMs < ONE_MS){}
}
