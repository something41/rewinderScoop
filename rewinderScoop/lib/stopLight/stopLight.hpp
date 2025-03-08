#include "stdint.h"

#define LED_OFF (HIGH)
#define LED_ON  (LOW)


typedef enum
{
    RED,
    YELLOW,
    GREEN,
    CLEAR,
} stopLight_display_type_t;
typedef struct
{
    const uint32_t redPin;
    const uint32_t yellowPin;
    const uint32_t greenPin;
    uint32_t errorCounter;
    bool showingError;
    stopLight_display_type_t displayType;

} stopLight_t;

#define STOPLIGHT_INIT(_redPin, _yellowPin, _greenPin) \
{ \
    .redPin    = _redPin, \
    .yellowPin = _yellowPin, \
    .greenPin  = _greenPin, \
    .errorCounter = 0, \
    .showingError = false, \
    .displayType = CLEAR, \
}


void stopLight__clear(stopLight_t * stopLight);
void stopLight__setRed(stopLight_t * stopLight);
void stopLight__setYellow(stopLight_t * stopLight);
void stopLight__setGreen(stopLight_t * stopLight);
void stopLight__update(stopLight_t * stopLight);
void stopLight__init(stopLight_t * stopLight);
void stopLight__error(stopLight_t * stopLight);

