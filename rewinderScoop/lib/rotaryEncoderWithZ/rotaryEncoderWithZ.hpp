#include "Arduino.h"
#include "rotaryEncoder.hpp"

typedef struct
{
    rotaryEncoder_t abEncoder;
    struct
    {
        uint32_t pin;
        uint32_t count;
        uint32_t scale;
    } z;
    uint32_t actualDistance;

} rotaryEncoderWithZ_t;

#define ROTARY_ENCODER_WITH_Z_INIT(_pinA, _pinB, _pinZ, _abScaleFactor, _debounce, _zScale) { \
    .abEncoder = ROTARY_ENCODER_INIT(_pinA, _pinB, _scaleFactor, _debounce), \
    . z { \
        .pin = _pinZ, \
        .count = 0, \
        .scale = _zscale, \
    }, \
    .actualDistance, \
}

void rotaryEncoderWithZ__init(rotaryEncoderWithZ_t * encoder);

uint32_t rotaryEncoderWithZ__update(rotaryEncoderMode_t * encoder);

uint32_t rotaryEncoderWithZ__getReading(rotaryEncoderMode_t * encoder);





