#include <Arduino.h>

#include "application.hpp"

#include "motor.hpp"

#include "ledDisplay.hpp"
#include "sevenSegmentDisplay.hpp"
#include "button.hpp"
#include "knob.hpp"
#include "dial.hpp"
#include "zCounter.hpp"

//#include "rotaryEncoderWithZ.hpp"
#include "rotaryEncoder.hpp"

system_t rewinder = SYSTEM_INIT();

motor_t motorObj = MOTOR_INIT(PIN_MOTOR, MOTOR_RAMP_TIME_MS);
motor_t * motor = &motorObj;

//rotaryEncoder_t encoderObj = ROTARY_ENCODER_INIT(PIN_ENCODER_A, PIN_ENCODER_B, ENCODER_SCALE_VALUE_INCHES_PER_TICK, ENCODER_ERROR_DEBOUNCE_MS);
//rotaryEncoder_t * encoder = &encoderObj;

zCounter_t zCounterObj = ZCOUNTER_INIT(PIN_ENCODER_Z, ENCODER_Z_COUNT_SCALE, ENCODER_Z_TIME_OUT_MS);
zCounter_t *zCounter = &zCounterObj;

ledDisplay_t stopLightObj = LED_DISPLAY_INIT(PIN_LED_RED, PIN_LED_YELLOW, PIN_LED_GREEN);
ledDisplay_t * stopLight = &stopLightObj;

sevenSegmentDisplay_t sevenSegmentDisplayObj = SEVEN_SEGMENT_DISPLAY_INIT(DEFAULT_I2C_ADDRESS);
sevenSegmentDisplay_t * sevenSegmentDisplay = &sevenSegmentDisplayObj;

button_t startButtonObj = BUTTON_INIT(PIN_START_BUTTON);
button_t * startButton = &startButtonObj;

knob_t knobObj = KNOB_INIT(PIN_KNOB_A, PIN_KNOB_B, PIN_KNOB_C, PIN_KNOB_D);
knob_t * knob = &knobObj;

dial_t customDistanceDialObj = DIAL_INIT(D14, CUSTOM_DISTANCE_MIN, CUSTOM_DISTANCE_MIN, CUSTOM_KNOB_RESOLUTION);
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

static inline uint32_t getCustomDistance2(uint32_t value)
{
	return (1 - CUSTOM_PERCENT_FAST) * value;
}
static inline uint32_t getCustomDistance1(uint32_t value)
{
	return value - getCustomDistance2(value);
}

static void setCustomDistance(uint32_t value)
{
	rewinder.jobSelections[CUSTOM_JOB_INDEX].runs[0].distanceInFeet = getCustomDistance1(value);
	rewinder.jobSelections[CUSTOM_JOB_INDEX].runs[1].distanceInFeet = getCustomDistance2(value);
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
	Serial.print("encoder scale: ");
}
double previous = 0;
void loop()
{
	debugCounter++;
	uint32_t currentMillis = millis();

//	Serial.println(abzEncoder__getValue(encoder));
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

	if (selection == KNOB_MAX_VALUE)
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

	uint32_t jobLength = getCurrentJobDistance();


	ledDisplay__setStop(stopLight);

	sevenSegementDisplay__displayValue(sevenSegmentDisplay, jobLength);

	if (button__getStatus(startButton) == true)
	{
		return SYSTEM_STATE_START;
	}
	return SYSTEM_STATE_SETUP;
}

systemState_t startState()
{
	zCounter__reset(zCounter);
	zCounter__enterRunMode(zCounter);

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

	uint32_t feetPulled = zCounter__getScaledCount(zCounter);

	sevenSegementDisplay__displayValue(sevenSegmentDisplay, feetPulled);

	if (feetPulled >= getCurrentRunDistance())
	{
		// Hooray! We finished a run
		rewinder.runIndex++;

		return rewinder.runIndex >= 2 ? SYSTEM_STATE_FINISH : SYSTEM_STATE_TRANSITION_TO_RUN;
	}

	return SYSTEM_STATE_RUN;
}

systemState_t finishState()
{

	motor__stop(motor);
	ledDisplay__setStop(stopLight);
	zCounter__enterIdleMode(zCounter);

	return SYSTEM_STATE_SETUP;
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
	zCounter__update(zCounter);
	sevenSegmentDisplay__update(sevenSegmentDisplay);
	ledDisplay__update(stopLight);
	button__update(startButton);
	dial__update(customDistanceDial);


}

void system__init()
{
	sevenSegmentDisplay__init(sevenSegmentDisplay);
	motor__init(motor);
	ledDisplay__init(stopLight);
	button__init(startButton);
	zCounter__init(zCounter);
	knob__init(knob);
	dial__init(customDistanceDial);

}

void waitForNextMs(uint32_t currentMs)
{
	while (millis() - currentMs < ONE_MS){}
}
