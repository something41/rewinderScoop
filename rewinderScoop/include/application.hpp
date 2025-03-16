

#include "stdint.h"
#include "configuration.hpp"


#define ONE_MS         (1)

typedef enum
{
	SYSTEM_STATE_SETUP = 0,
	SYSTEM_STATE_START,
	SYSTEM_STATE_TRANSITION_TO_RUN,
	SYSTEM_STATE_RUN,
	SYSTEM_STATE_FINISH,
	SYSTEM_STATE_ERROR,
} systemState_t;


// a run is a telling the machine to run a certain distance and speed
typedef struct
{
	uint32_t distanceInFeet;
	uint32_t percentSpeed;
} run_t;

// a job consists of two runs
typedef struct
{
	run_t runs[2];
} job_t;

typedef struct
{
	systemState_t currentState;
    systemState_t previousState;
	job_t jobSelections[11];
	uint32_t runIndex;
    uint32_t jobIndex;
} system_t;


#define CREATE_RUN(_distance, _speed) \
{ \
	.distanceInFeet = _distance, \
	.percentSpeed = _speed, \
}

#define CREATE_JOB_FULL_INIT(_distance0, _speed0, _distance1, _speed1) \
{ \
	.runs = {CREATE_RUN(_distance0, _speed0), CREATE_RUN(_distance1, _speed1)}, \
}

#define CREATE_JOB(_distance0, _distance1) CREATE_JOB_FULL_INIT(_distance0, RUN_SPEED_1_DEFAULT, _distance0 + _distance1, RUN_SPEED_2_DEFAULT)

#define SYSTEM_INIT() { \
    .currentState = SYSTEM_STATE_SETUP, \
    .previousState = SYSTEM_STATE_SETUP, \
    .jobSelections = { \
            JOB_0, \
            JOB_1, \
            JOB_2, \
            JOB_3, \
            JOB_4, \
            JOB_5, \
            JOB_6, \
            JOB_7, \
            JOB_8, \
            JOB_9, \
            JOB_10, \
        }, \
} \

#define CUSTOM_JOB_INDEX (10)

void system__init();
void system__update();


systemState_t setupState();
systemState_t startState();
systemState_t runState();
systemState_t transitionToRunState();
systemState_t finishState();
systemState_t errorState();

void waitForNextMs(uint32_t currentMs);