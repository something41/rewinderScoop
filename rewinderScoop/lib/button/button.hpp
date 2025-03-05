#include "stdint.h"
#include "Arduino.h"
#include "debounce.hpp"

#define DEFAULT_DEBOUNCE_TIME_MS (10)

typedef struct 
{
    const uint32_t pin;
    debounce_t debounce;
} button_t;

#define BUTTON_INIT(_pin) \
{ \
    .pin = _pin, \
    .debounce = DEBOUNCE_INIT_DEFAULT(), \
}

//return true if state changes
bool button__update(button_t * button);

bool button__getStatus(button_t * button);

void button__init(button_t * button);


