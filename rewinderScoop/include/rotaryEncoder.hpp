#include "stdint.h"
#define ENCODER_OPTIMIZE_INTERRUPTS
#include "Encoder.h"
typedef struct
{
    const double scaleFactor;
    Encoder encoder;
} rotaryEncoder;



#define ROTARY_ENCODER_INIT(_pinA, _pinB, _scaleFactor) { \
    .scaleFactor = _scaleFactor, \
    .encoder = {_pinA, _pinB}, \
}

double rotaryEncoder__getScaledValue(rotaryEncoder * encoder);

void rotaryEncoder__setScaledValue(rotaryEncoder * encoder, double value);

void rotaryEncoder__reset(rotaryEncoder * encoder);

void rotaryEncoder__update(rotaryEncoder * encoder);