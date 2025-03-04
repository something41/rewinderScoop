#include "rotaryEncoder.hpp"

double rotaryEncoder__getScaledValue(rotaryEncoder * encoder)
{
    return encoder->encoder.read() * encoder->scaleFactor;
}

void rotaryEncoder__setScaledValue(rotaryEncoder * encoder, double value)
{
    encoder->encoder.write(value/encoder->scaleFactor);
}

void rotaryEncoder__reset(rotaryEncoder * encoder)
{
    encoder->encoder.write(0);
}