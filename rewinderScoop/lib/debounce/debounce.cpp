#include "debounce.hpp"

bool debounce__update(debounce_t * debounce, uint32_t sampledValue)
{
    if (sampledValue == debounce->previousSample)
    {
        if (debounce->counterMs++ == debounce->debounceTimeMs)
        {
            if (debounce->status != sampledValue)
            {
                debounce->status = sampledValue;
                return true;
            }

        } 
    }
    else {
        debounce->counterMs = 0;
        debounce->previousSample = sampledValue;

    }


    return false;
}

uint32_t debounce__getStatus(debounce_t * debounce)
{
    return debounce->status;
}

void debounce__init(debounce_t * debounce)
{
    debounce->previousSample = 0;
    debounce->status = 0;
    debounce->counterMs = 0;
}

