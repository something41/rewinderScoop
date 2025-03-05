#include "stdint.h"
#include "Arduino.h"

#define DEFAULT_DEBOUNCE_TIME_MS (10)

typedef struct 
{
    const uint32_t pin;
    const uint32_t debounceTimeMs;
    bool status;
    bool previousStatus;
    uint32_t startTime;
} button_t;

#define BUTTON_INIT(_pin) \
{ \
    .pin = _pin, \
    .debounceTimeMs = DEFAULT_DEBOUNCE_TIME_MS, \
    .status = false, \
    .previousStatus = false, \
    .startTime = 0, \
}

//return true if state changes
bool button__update(button_t * button);

bool button__getStatus(button_t * button);

void button__init(button_t * button);


