#include "debounce.hpp"

bool debounce__update(debounce_t * debounce, boolean sampledValue)
{
    uint32_t timer = millis();

    if (sampledValue != debounce->previousStatus)
    {
        debounce->startTime = timer;
    }

    debounce->previousStatus = sampledValue;

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
    debounce->previousStatus = false;
    debounce->status = false;
    debounce->startTime = 0;
}

