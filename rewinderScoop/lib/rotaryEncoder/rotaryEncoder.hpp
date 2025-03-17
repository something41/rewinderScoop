#include "Arduino.h"
#include "stdint.h"
#include "debounce.hpp"

#define ENCODER_BYPASS_ERROR_DEBOUNCE (0)

typedef enum
{
    IDLE,
    RUNNING,
    FINISH,
} rotaryEncoderMode_t;

typedef struct
{
    const float multiplier;
    const float divider;
    uint32_t accurateCount;
    const uint32_t aCountPerRevolution;
    bool calibrationComplete;
    uint32_t pinA;
    uint32_t pinZ;
    struct
    {
        uint32_t a;
        uint32_t z;
    } counter;
    struct
    {
        uint32_t a;
        uint32_t z;
    } previousCounter;
    debounce_t debounceError;
    debounce_t debounceFinish;
    rotaryEncoderMode_t mode;
} rotaryEncoder_t;

#define ROTARY_ENCODER_INIT(_pinA, _pinZ, _multiplier, _divider, _aCountPerRevolution, _debounceError, _debounceFinish) \
{ \
    .multiplier = _multiplier, \
    .divider = _divider, \
    .accurateCount = 0, \
    .aCountPerRevolution = _aCountPerRevolution, \
    .calibrationComplete = false, \
    .pinA = _pinA, \
    .pinZ = _pinZ, \
    .counter = { \
        .a = 0, \
        .z = 0, \
    }, \
    .previousCounter = { \
        .a = 0, \
        .z = 0, \
    }, \
    .debounceError = DEBOUNCE_INIT(_debounceError), \
    .debounceFinish = DEBOUNCE_INIT(_debounceFinish), \
    .mode = IDLE, \
}

float rotaryEncoder__getScaledValue(rotaryEncoder_t * encoder);

void rotaryEncoder__setScaledValue(rotaryEncoder_t * encoder, double value);

void rotaryEncoder__reset(rotaryEncoder_t * encoder);

void rotaryEncoder__update(rotaryEncoder_t * encoder);

void rotaryEncoder__enterIdleMode(rotaryEncoder_t * encoder);

void rotaryEncoder__enterRunMode(rotaryEncoder_t * encoder);

void rotaryEncoder__enterFinishMode(rotaryEncoder_t * encoder);

boolean rotaryEncoder__stallErrorDetected(rotaryEncoder_t * encoder);

void rotaryEncoder__init(rotaryEncoder_t * encoder);

uint32_t rotaryEncoder__getTotalCount(rotaryEncoder_t * encoder);

boolean rotaryEncoder__isFinished(rotaryEncoder_t * encoder);