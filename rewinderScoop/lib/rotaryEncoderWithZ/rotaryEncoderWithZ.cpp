#include "rotaryEncoderWithZ.hpp"

static void zISR(void * instance)
{
    rotaryEncoderWithZ_t * encoder = (rotaryEncoderWithZ_t * ) instance;
    encoder->z.count++;
}

void rotaryEncoderWithZ__init(rotaryEncoderWithZ_t * encoder)
{
    pinMode(encoder->z.pin, INPUT);
    attachInterruptArg(digitalPinToInterrupt(encoder->z.pin), zISR, encoder, RISING);
}

uint32_t rotaryEncoderWithZ__update(rotaryEncoderMode_t * encoder)
{

    return 0;
}

uint32_t rotaryEncoderWithZ__getReading(rotaryEncoderMode_t * encoder)
{
    return encoder->z.count * encoder->z.scale;
}