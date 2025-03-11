#include "Arduino.h"
#include "dial.hpp"


#define MAX_DISPLAY_NUM (9999)

#define MIN_RAW_ANALOG_READING (0)


void dial__init(dial_t * dial)
{

    analogReadResolution(dial->resolution);

    if (dial->maxValue > MAX_DISPLAY_NUM)
    {
        dial->maxValue = MAX_DISPLAY_NUM;
    }
}

uint32_t dial__update(dial_t * dial)
{
    dial->rawReading = analogRead(dial->pin);

    dial->cachedValue = map(dial->rawReading, MIN_RAW_ANALOG_READING, (1 << dial->resolution) - 1, dial->minValue, dial->maxValue);
}

uint32_t dial__getRawReading(dial_t * dial)
{
    return dial->rawReading;
}

uint32_t dial__getReading(dial_t * dial)
{
    return dial->cachedValue;
}