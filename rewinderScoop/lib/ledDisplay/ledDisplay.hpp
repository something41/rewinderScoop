#include "stdint.h"

#define LED_OFF (HIGH)
#define LED_ON  (LOW)

#define LED_ERROR_DISPLAY_TIME_MS (100)

typedef enum
{
    DISPLAY_TYPE__STOP,
    DISPLAY_TYPE__SLOW,
    DISPLAY_TYPE__FAST,
    DISPLAY_TYPE__CLEAR,
    DISPLAY_TYPE__ERROR,
    DISPLAY_TYPE__FINISH,
} stopLight_display_type_t;

typedef struct
{
    const uint32_t redPin;
    const uint32_t yellowPin;
    const uint32_t greenPin;
    uint32_t errorCounter;
    bool showingError;
    stopLight_display_type_t displayType;
    bool isDone;
    uint32_t counterMs;

} ledDisplay_t;

#define LED_DISPLAY_INIT(_redPin, _yellowPin, _greenPin) \
{ \
    .redPin    = _redPin, \
    .yellowPin = _yellowPin, \
    .greenPin  = _greenPin, \
    .errorCounter = 0, \
    .showingError = false, \
    .displayType = DISPLAY_TYPE__CLEAR, \
    .isDone = false, \
    .counterMs = 0 \
}

void ledDisplay__setClear(ledDisplay_t * stopLight);

void ledDisplay__setStop(ledDisplay_t * stopLight);

void ledDisplay__setSlow(ledDisplay_t * stopLight);

void ledDisplay__setFast(ledDisplay_t * stopLight);

void ledDisplay__setError(ledDisplay_t * stopLight);

void ledDisplay__setFinish(ledDisplay_t * ledDisplay);

void ledDisplay__update(ledDisplay_t * stopLight);

void ledDisplay__init(ledDisplay_t * stopLight);

void ledDisplay__setError(ledDisplay_t * stopLight);

bool ledDisplay__isDone(ledDisplay_t * stopLight);

