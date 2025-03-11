#include "stdint.h"
//#define ENCODER_OPTIMIZE_INTERRUPTS
#include "debounce.hpp"

#define ENCODER_BYPASS_ERROR_DEBOUNCE (0)

typedef enum
{
    IDLE,
    RUNNING,
} rotaryEncoderMode_t;

typedef struct
{
    const double scaleFactor;
    Encoder encoder;
    debounce_t debounceError;
    rotaryEncoderMode_t mode;
    int32_t previousCount;
    int32_t currentCount;
} rotaryEncoder_t;

#define ROTARY_ENCODER_INIT_FULL(_pinA, _pinB, _scaleFactor, _debounceAmount) \
{ \
    .scaleFactor = _scaleFactor, \
    .encoder = {_pinA, _pinB}, \
    .debounceError = DEBOUNCE_INIT(_debounceAmount), \
    .mode = IDLE, \
    .previousCount = 0, \
    .currentCount = 0, \
}

#define ROTARY_ENCODER_NO_ERROR(_pinA, _pinB, _scaleFactor) ROTARY_ENCODER_INIT_FULL(_pinA, _pinB, _scaleFactor, 0)

#define ROTARY_ENCODER_INIT(_pinA, _pinB, _scaleFactor, _debounce) ROTARY_ENCODER_INIT_FULL(_pinA, _pinB, _scaleFactor, _debounce)

double rotaryEncoder__getScaledValue(rotaryEncoder_t * encoder);

void rotaryEncoder__setScaledValue(rotaryEncoder_t * encoder, double value);

void rotaryEncoder__reset(rotaryEncoder_t * encoder);

void rotaryEncoder__update(rotaryEncoder_t * encoder);

void rotaryEncoder__enterIdleMode(rotaryEncoder_t * encoder);

void rotaryEncoder__enterRunMode(rotaryEncoder_t * encoder);

boolean rotaryEncoder__stallErrorDetected(rotaryEncoder_t * encoder);

void rotaryEncoder__init(rotaryEncoder_t * encoder);