#include "stdint.h"

#define ONE_MS         (1)

typedef enum 
{
  SYSTEM_STATE_SETUP = 0,
  SYSTEM_STATE_START,
  SYSTEM_STATE_RUNNING,
  SYSTEM_STATE_FINISH
} systemState_t;

