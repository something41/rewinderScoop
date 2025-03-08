#include "stdint.h"

#define LED_OFF (HIGH)
#define LED_ON  (LOW)


typedef enum
{
    STOP,
    SLOW,
    FAST,
    CLEAR,
    ERROR,
} stopLight_display_type_t;

typedef struct
{
    const uint32_t redPin;
    const uint32_t yellowPin;
    const uint32_t greenPin;
    uint32_t errorCounter;
    bool showingError;
    stopLight_display_type_t displayType;
    struct {
        uint32_t counterMs;
    } error;

} ledDisplay_t;

#define LED_DISPLAY_INIT(_redPin, _yellowPin, _greenPin) \
{ \
    .redPin    = _redPin, \
    .yellowPin = _yellowPin, \
    .greenPin  = _greenPin, \
    .errorCounter = 0, \
    .showingError = false, \
    .displayType = CLEAR, \
    .error = { \
        0 \
    }, \
}

void ledDisplay__setClear(ledDisplay_t * stopLight);
void ledDisplay__setStop(ledDisplay_t * stopLight);
void ledDisplay__setSlow(ledDisplay_t * stopLight);
void ledDisplay__setFast(ledDisplay_t * stopLight);
void ledDisplay__setError(ledDisplay_t * stopLight);
void ledDisplay__update(ledDisplay_t * stopLight);
void ledDisplay__init(ledDisplay_t * stopLight);
void ledDisplay__error(ledDisplay_t * stopLight);

