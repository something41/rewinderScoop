#include "stdint.h"

#define ONE_MS         (1)

#define RUN_SPEED_1_DEFAULT (100)
#define RUN_SPEED_2_DEFAULT (35)

typedef enum 
{
	SYSTEM_STATE_SETUP = 0,
	SYSTEM_STATE_START,
	SYSTEM_STATE_TRANISITION_TO_RUN_0,
	SYSTEM_STATE_RUN_0,
	SYSTEM_STATE_TRANISITION_TO_RUN_1,
	SYSTEM_STATE_RUN_1,
	SYSTEM_STATE_FINISH,
	SYSTEM_STATE_ERROR,
} systemState_t;

typedef struct
{
	uint32_t distanceInFeet;
	uint32_t percentSpeed;
} run_t;

typedef struct
{
	run_t runs[2];
	uint32_t index;
} job_t;

#define CREATE_RUN(_distance, _speed) \
{ \
	.distanceInFeet = _distance, \
	.percentSpeed = _speed, \
}

#define CREATE_JOB_FULL_INIT(_distance0, _speed0, _distance1, _speed1) \
{ \
	.runs = {CREATE_RUN(_distance0, _speed0), CREATE_RUN(_distance1, _speed1)}, \
	.index = 0, \
}

#define CREATE_JOB(_distance0, _distance1) CREATE_JOB_FULL_INIT(_distance0, RUN_SPEED_1_DEFAULT, _distance1, RUN_SPEED_2_DEFAULT) 



void system__init();

void system__update();

systemState_t setupState();
systemState_t startState();
systemState_t run0State();
systemState_t transitionToRun1State();
systemState_t transitionToRun0State();
systemState_t run1State();
systemState_t finishState();
systemState_t errorState();

void waitForNextMs(uint32_t currentMs);