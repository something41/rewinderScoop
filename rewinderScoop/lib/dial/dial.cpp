#include "Arduino.h"
#include "dial.hpp"

void dial__init(dial_t * dial)
{

}

uint32_t dial__update(dial_t * dial)
{
    dial->rawReading = analogRead(dial->pin);

    return dial->scale * dial->rawReading;
}

uint32_t dial__getRawReading(dial_t * dial)
{
    return dial->rawReading;
}

uint32_t dial__getReading(dial_t * dial)
{
    return dial->scale * dial->rawReading;
}