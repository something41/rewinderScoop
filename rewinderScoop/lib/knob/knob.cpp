#include "knob.hpp"
#include <Arduino.h>

void knob__init(knob_t * knob)
{

}

uint32_t knob__update(knob_t * knob)
{
    //todo check thresholds
    uint32_t reading = analogRead(knob->pin);
}

uint32_t knob__getSelection(knob_t * knob)
{
    return knob->selection;
}