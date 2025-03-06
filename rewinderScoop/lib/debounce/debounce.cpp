#include "debounce.hpp"

bool debounce__update(debounce_t * debounce, boolean sampledValue)
{
    uint32_t timer = millis();

    if (sampledValue != debounce->previousSample)
    {
        debounce->startTime = timer;
    }

    debounce->previousSample = sampledValue;

    if (timer - debounce->startTime  > debounce->debounceTimeMs)
    {
        if (sampledValue != debounce->status)
        {
            debounce->status = sampledValue;
            return true;
        }
    }

    return false;
}

bool debounce__getStatus(debounce_t * debounce)
{
    return debounce->status;
}

void debounce__init(debounce_t * debounce)
{
    debounce->previousSample = false;
    debounce->status = false;
    debounce->startTime = 0;
}

