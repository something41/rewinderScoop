#include "Arduino.h"
#include "dial.hpp"


#define MAX_DISPLAY_NUM (9999)

#define MIN_RAW_ANALOG_READING (0)

void dial__init(dial_t * dial)
{
    if (dial->maxValue > MAX_DISPLAY_NUM)
    {
        dial->maxValue = MAX_DISPLAY_NUM;
    }

}

uint32_t dial__update(dial_t * dial)
{
    dial->rawReading = analogRead(dial->pin);
    dial->cachedValueFiltered  =  dial->cachedValueFiltered - (.01 * (dial->cachedValueFiltered  - dial->rawReading));

    dial->cachedValue = map(dial->cachedValueFiltered, 432, 16200, dial->minValue, dial->maxValue);

    return dial->cachedValue;
}

uint32_t dial__getRawReading(dial_t * dial)
{
    return dial->rawReading;
}

uint32_t dial__getReading(dial_t * dial)
{
    return dial->cachedValue;
}