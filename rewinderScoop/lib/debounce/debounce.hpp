#include "stdint.h"
#include "Arduino.h"

#define DEFAULT_DEBOUNCE_TIME_MS (10)

typedef struct 
{
    const uint32_t debounceTimeMs;
    bool status;
    bool previousStatus;
    uint32_t startTime;
} debounce_t;

#define DEBOUNCE_INIT(_debounceTimeMs) \
{ \
    .debounceTimeMs = DEFAULT_DEBOUNCE_TIME_MS, \
    .status = false, \
    .previousStatus = false, \
    .startTime = 0, \
}

#define DEBOUNCE_INIT_DEFAULT() DEBOUNCE_INIT(DEFAULT_DEBOUNCE_TIME_MS)


//return true if state changes
bool debounce__update(debounce_t * debounce, boolean sampledValue);

bool debounce__getStatus(debounce_t * debounce);

void debounce__init(debounce_t * debounce);


