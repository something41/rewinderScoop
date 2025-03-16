#include "Arduino.h"
#include "debounce.hpp"

typedef enum
{
    ZCOUNTER_IDLE = 0,
    ZCOUNTER_RUNNING = 0,
} zCounter_mode_t;

typedef struct 
{
    uint32_t pin;
    zCounter_mode_t mode;
    float scale;
    uint32_t counter;
    uint32_t previousCount;
    debounce_t debounceError;
} zCounter_t;

#define ZCOUNTER_INIT(_pin, _scale, _debounceTimeMS) \
{ \
    .pin = _pin, \
    .mode = ZCOUNTER_IDLE, \
    .scale =  _scale, \
    .counter = 0, \
    .previousCount = 0, \
    .debounceError = DEBOUNCE_INIT(_debounceTimeMS) \
}

void zCounter__init(zCounter_t * zCounter);

void zCounter__update(zCounter_t * zCounter);

float zCounter__getScaledCount(zCounter_t * zCounter);

void zCounter__reset(zCounter_t * zCounter);

void zCounter__enterRunMode(zCounter_t * zCounter);

void zCounter__enterIdleMode(zCounter_t * zCounter);

boolean zCounter__stallErrorDetected(zCounter_t * zCounter);