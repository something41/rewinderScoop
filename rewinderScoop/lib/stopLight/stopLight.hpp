#include "stdint.h"

#define LED_OFF (HIGH)
#define LED_ON  (LOW)

typedef struct
{
    const uint32_t redPin;
    const uint32_t yellowPin;
    const uint32_t greenPin;
} stopLight_t;

#define STOPLIGHT_INIT(_redPin, _yellowPin, _greenPin) \
{ \
    .redPin    = _redPin, \
    .yellowPin = _yellowPin, \
    .greenPin  = _greenPin, \
}


void stopLight__clear(stopLight_t * stopLight);
void stopLight__setRed(stopLight_t * stopLight);
void stopLight__setYellow(stopLight_t * stopLight);
void stopLight__setGreen(stopLight_t * stopLight);
void stopLight__update(stopLight_t * stopLight);

