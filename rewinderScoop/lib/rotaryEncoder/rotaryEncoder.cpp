#include "rotaryEncoder.hpp"

static void zISR(void * instance)
{
    rotaryEncoder_t * encoder = (rotaryEncoder_t * ) instance;
    encoder->counter.z++;
    if (!encoder->calibrationComplete)
    {
        //We don't know where we are in the cycle until the first pulse
        encoder->accurateCount = encoder->counter.a;
        encoder->calibrationComplete = true;
    }
    else
    {
        // every time z pulses from now on, we can throw away our a counts
        // and replace with more accurate z count.
        encoder->accurateCount += encoder->aCountPerRevolution;
        encoder->counter.a = 0;
    }

}

static void aISR(void * instance)
{
    rotaryEncoder_t * encoder = (rotaryEncoder_t * ) instance;
    encoder->counter.a++;
}

uint32_t rotaryEncoder__getTotalCount(rotaryEncoder_t * encoder)
{
    return (encoder->accurateCount + encoder->counter.a);
}

float rotaryEncoder__getScaledValue(rotaryEncoder_t * encoder)
{
    return ((rotaryEncoder__getTotalCount(encoder)) * 5.9)/100;
}

void rotaryEncoder__reset(rotaryEncoder_t * encoder)
{
    encoder->mode = IDLE;
    encoder->previousCounter = {0};
    encoder->counter = {0};
    encoder->accurateCount = 0;
    encoder->calibrationComplete = false;
    debounce__init(&encoder->debounceError);
}

void rotaryEncoder__update(rotaryEncoder_t * encoder)
{
    if (encoder->mode == RUNNING)
    {
        debounce__update(&encoder->debounceError, encoder->previousCounter.a == encoder->counter.a);
    }

    if (encoder->mode == FINISH)
    {
        debounce__update(&encoder->debounceFinish, encoder->previousCounter.a == encoder->counter.a);
    }

    encoder->previousCounter.a = encoder->counter.a;
#if (ENABLE_DEBUG)
    if (encoder->previousCounter.z != encoder->counter.z)
    {
        Serial.print(encoder->counter.z);
        encoder->previousCounter.z = encoder->counter.z;
        Serial.print(" ");
        Serial.println(rotaryEncoder__getScaledValue(encoder));
    }
#endif
}

void rotaryEncoder__init(rotaryEncoder_t * encoder)
{
    pinMode(encoder->pinA, INPUT_PULLUP);
    pinMode(encoder->pinZ, INPUT_PULLUP);
    attachInterruptParam(digitalPinToInterrupt(encoder->pinA), aISR, RISING, encoder);
    attachInterruptParam(encoder->pinZ, zISR, RISING, encoder);
    debounce__init(&encoder->debounceError);
    debounce__init(&encoder->debounceFinish);
}

void rotaryEncoder__enterRunMode(rotaryEncoder_t * encoder)
{
    encoder->mode = RUNNING;
}

void rotaryEncoder__enterIdleMode(rotaryEncoder_t * encoder)
{
    encoder->mode = IDLE;
}

void rotaryEncoder__enterFinishMode(rotaryEncoder_t * encoder)
{
    encoder->mode = FINISH;
}

boolean rotaryEncoder__stallErrorDetected(rotaryEncoder_t * encoder)
{
    if (encoder->debounceError.debounceTimeMs == 0)
    {
        return false;
    }

    return debounce__getStatus(&encoder->debounceError);
}

boolean rotaryEncoder__isFinished(rotaryEncoder_t * encoder)
{
    if (encoder->mode != FINISH)
    {
        return false;
    }

    return debounce__getStatus(&encoder->debounceFinish);
}