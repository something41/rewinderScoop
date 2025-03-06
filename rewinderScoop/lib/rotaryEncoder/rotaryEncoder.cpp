#include "rotaryEncoder.hpp"

double rotaryEncoder__getScaledValue(rotaryEncoder_t * encoder)
{
    return encoder->encoder.read() * encoder->scaleFactor;
}

void rotaryEncoder__setScaledValue(rotaryEncoder_t * encoder, double value)
{
    encoder->encoder.write(value/encoder->scaleFactor);
}

void rotaryEncoder__reset(rotaryEncoder_t * encoder)
{
    encoder->encoder.write(0);
    encoder->mode = IDLE;
    encoder->previousCount = 0;
    debounce__init(&encoder->debounceError);
}

void rotaryEncoder__update(rotaryEncoder_t * encoder)
{
    if (encoder->mode == RUNNING)
    {
        encoder->previousCount = encoder->encoder.read();
        debounce__update(&encoder->debounceError, encoder->previousCount == encoder->encoder.read());
    }
}

void rotaryEncoder__init(rotaryEncoder_t * encoder)
{
    debounce__init(&encoder->debounceError);
}

void rotaryEncoder__enterRunMode(rotaryEncoder_t * encoder)
{
    encoder->mode = RUNNING;
}

void rotaryEncoder__enterIdleMode(rotaryEncoder_t * encoder)
{
    encoder->mode = IDLE;
}

boolean rotaryEncoder__stallErrorDetected(rotaryEncoder_t * encoder)
{
    if (encoder->debounceError.debounceTimeMs == 0)
    {
        return false;
    }

    return debounce__getStatus(&encoder->debounceError);
}