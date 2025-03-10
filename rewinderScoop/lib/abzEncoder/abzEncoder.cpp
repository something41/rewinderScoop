#include "abzEncoder.hpp"
#include "Arduino.h"

// todo: ab are factional rotations, not using them now unless we need to

static void zISR(void * instance)
{
    abzEncoder_t * encoder = (abzEncoder_t *) instance;
    encoder->countOf.z++;

    // clear a and b, since we know we did a whole rev
    encoder->countOf.a = 0;
    encoder->countOf.b = 0;

    encoder->totalCounter++;
}

static void aISR(void * instance)
{
    abzEncoder_t * encoder = (abzEncoder_t *) instance;
    encoder->countOf.a++;
    encoder->totalCounter++;
    if (UNUSED_PIN != encoder->pin.b)
    {
        if (digitalRead(encoder->pin.a))
        {
            encoder->direction = DIRECTION__NEGATIVE;
        }
        else
        {
            encoder->direction = DIRECTION__POSITIVE;
        }
    }
}

static void bISR(void * instance)
{
    abzEncoder_t * encoder = (abzEncoder_t *) instance;
    encoder->countOf.b++;
    encoder->totalCounter++;
}

void abzEncoder__init(abzEncoder_t * encoder)
{
    if (UNUSED_PIN != encoder->pin.a)
    {
        pinMode(encoder->pin.a, INPUT);
        uint32_t val = digitalPinToInterrupt(encoder->pin.a);
        Serial.println(val);
        while(1);
        //attachInterruptArg(digitalPinToInterrupt(encoder->pin.a), aISR, encoder, RISING);


    }
    if (UNUSED_PIN != encoder->pin.b)
    {
        pinMode(encoder->pin.b, INPUT);
        attachInterruptArg(digitalPinToInterrupt(encoder->pin.b), bISR, encoder, RISING);

    }
    if (UNUSED_PIN != encoder->pin.z)
    {
        pinMode(encoder->pin.z, INPUT);
        attachInterruptArg(digitalPinToInterrupt(encoder->pin.z), zISR, encoder, RISING);
    }

    debounce__init(&encoder->debounceError);
}

void abzEncoder__update(abzEncoder_t * encoder)
{
    if (DEBOUNCE_DISABLED_TIME_MS != debounce__getDebounceTimeMs(&encoder->debounceError))
    {
        debounce__update(&encoder->debounceError, encoder->totalCounter);
    }
}

uint32_t abzEncoder__getValue(abzEncoder_t * encoder)
{
    return encoder->countOf.z * encoder->scaleInFeet.z + encoder->countOf.a * encoder->scaleInFeet.ab + encoder->countOf.b * encoder->scaleInFeet.ab;
}

void abzEncoder__reset(abzEncoder_t * encoder)
{
    encoder->countOf.a = 0;
    encoder->countOf.b = 0;
    encoder->countOf.z = 0;
}

encoder_direction_t abzEncoder__getDirection(abzEncoder_t * encoder)
{
    return encoder->direction;
}

bool abzEncoder__stallErrorDetected(abzEncoder_t * encoder)
{
    return debounce__getStatus(&encoder->debounceError);
}
