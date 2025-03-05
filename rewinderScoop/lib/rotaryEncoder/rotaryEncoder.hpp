#include "stdint.h"
#define ENCODER_OPTIMIZE_INTERRUPTS
#include "Encoder.h"
#include "debounce.hpp"

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
    uint32_t previousCount;
} rotaryEncoder_t;



#define ROTARY_ENCODER_INIT(_pinA, _pinB, _scaleFactor) { \
    .scaleFactor = _scaleFactor, \
    .encoder = {_pinA, _pinB}, \
    .debounceError = DEBOUNCE_INIT(1000), \
    .mode = IDLE, \
    .previousCount = 0, \
}

double rotaryEncoder__getScaledValue(rotaryEncoder_t * encoder);

void rotaryEncoder__setScaledValue(rotaryEncoder_t * encoder, double value);

void rotaryEncoder__reset(rotaryEncoder_t * encoder);

void rotaryEncoder__update(rotaryEncoder_t * encoder);

void rotaryEncoder__enterIdleMode(rotaryEncoder_t * encoder);

void rotaryEncoder__enterRunMode(rotaryEncoder_t * encoder);

boolean rotaryEncoder__stallErrorDetected(rotaryEncoder_t * encoder);

void rotaryEncoder__init(rotaryEncoder_t * encoder);