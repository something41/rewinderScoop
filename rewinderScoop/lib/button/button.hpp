#include "stdint.h"
#include "Arduino.h"
#include "debounce.hpp"

typedef struct 
{
    const uint32_t pin;
    const uint32_t isInverted;
    debounce_t debounce;
} button_t;

#define BUTTON_INIT(_pin) \
{ \
    .pin = _pin, \
    .isInverted = false, \
    .debounce = DEBOUNCE_INIT_DEFAULT(), \
}

//return true if state changes
bool button__update(button_t * button);

bool button__getStatus(button_t * button);

void button__init(button_t * button);


