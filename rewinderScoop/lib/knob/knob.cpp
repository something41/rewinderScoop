#include "knob.hpp"
#include <Arduino.h>

uint32_t getSelectionFromRawReading(uint32_t reading)
{
    return 0;
}

void knob__init(knob_t * knob)
{

}


uint32_t knob__update(knob_t * knob)
{
    //todo check thresholds
    uint32_t reading = analogRead(knob->pin);
    
    return 0;
}

uint32_t knob__getSelection(knob_t * knob)
{
    return getSelectionFromRawReading(knob->currentReading);
}