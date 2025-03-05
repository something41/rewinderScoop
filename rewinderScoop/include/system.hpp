#include "stdint.h"

#define ONE_MS         (1)

typedef enum 
{
	SYSTEM_STATE_SETUP = 0,
	SYSTEM_STATE_START,
	SYSTEM_STATE_RUNNING,
	SYSTEM_STATE_FINISH
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
	.runs = {CREATE_RUN(_distance0, _speed0), CREATE_RUN(_distance1, _speed1)} \
	.index = 0, \
}

#define CREATE_JOB(_distance0, _distance1) CREATE_JOB_FULL_INIT(_distance0, _speed0, _distance1, _speed1) 