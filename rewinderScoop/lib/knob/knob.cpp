#include "knob.hpp"
#include <Arduino.h>

void knob__init(knob_t * knob)
{
    // todo is this pullup?
    pinMode(knob->pin.a, INPUT_PULLUP);
    pinMode(knob->pin.b, INPUT_PULLUP);
    pinMode(knob->pin.c, INPUT_PULLUP);
}

int32_t knob__update(knob_t * knob)
{
    knob->reading.a = digitalRead(knob->pin.a);
    knob->reading.b = digitalRead(knob->pin.b);
    knob->reading.c = digitalRead(knob->pin.c);
}

int32_t knob__getSelection(knob_t * knob)
{
    return knob->reading.value;
}