#include "zCounter.hpp"

static void isr(void * var)
{
    zCounter_t * zCounter = (zCounter_t *) var;
    zCounter->counter++;
}

void zCounter__init(zCounter_t * zCounter)
{
    zCounter->counter = 0;
    attachInterruptParam(zCounter->pin, isr, RISING, zCounter);
    debounce__init(&zCounter->debounceError);
}

void zCounter__update(zCounter_t * zCounter)
{
    if (zCounter->mode == ZCOUNTER_RUNNING)
    {
        debounce__update(&zCounter->debounceError, zCounter->previousCount == zCounter->counter);
        zCounter->previousCount = zCounter->counter;
    }
}

float zCounter__getScaledCount(zCounter_t * zCounter)
{
    return zCounter->counter * zCounter->scale;
}

void zCounter__reset(zCounter_t * zCounter)
{
    zCounter->counter = 0;
    zCounter->previousCount = 0;
}

void zCounter__enterRunMode(zCounter_t * zCounter)
{
    zCounter->mode = ZCOUNTER_RUNNING;
}

void zCounter__enterIdleMode(zCounter_t * zCounter)
{
    zCounter->mode = ZCOUNTER_IDLE;
}

boolean zCounter__stallErrorDetected(zCounter_t * zCounter)
{
    if (zCounter->debounceError.debounceTimeMs == 0)
    {
        return false;
    }

    return debounce__getStatus(&zCounter->debounceError);
}