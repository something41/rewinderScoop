#include "stdint.h"
#include "Arduino.h"

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#define DEFAULT_DEBOUNCE_TIME_MS (10)
#define DEBOUNCE_DISABLED_TIME_MS (0)

typedef struct
{
    const uint32_t debounceTimeMs;
    uint32_t status;
    uint32_t previousSample;
    uint32_t counterMs;
} debounce_t;

#define DEBOUNCE_INIT(_debounceTimeMs) \
{ \
    .debounceTimeMs = _debounceTimeMs, \
    .status = 0, \
    .previousSample = 0, \
    .counterMs = 0, \
}

#define DEBOUNCE_INIT_DEFAULT() DEBOUNCE_INIT(DEFAULT_DEBOUNCE_TIME_MS)


//return true if state changes
bool debounce__update(debounce_t * debounce, uint32_t sampledValue);

uint32_t debounce__getStatus(debounce_t * debounce);

void debounce__init(debounce_t * debounce);

uint32_t debounce__getDebounceTimeMs(debounce_t * debounce);

#endif

