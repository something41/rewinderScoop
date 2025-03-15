#include "knob.hpp"
#include <Arduino.h>

void knob__init(knob_t * knob)
{
    // todo is this pullup?
    pinMode(knob->pin.a, INPUT_PULLDOWN);
    pinMode(knob->pin.b, INPUT_PULLDOWN);
    pinMode(knob->pin.c, INPUT_PULLDOWN);
    pinMode(knob->pin.d, INPUT_PULLDOWN);
}
uint32_t pValue = 0;
int32_t knob__update(knob_t * knob)
{
    knob->reading.a = !digitalRead(knob->pin.a);
    knob->reading.b = !digitalRead(knob->pin.b);
    knob->reading.c = !digitalRead(knob->pin.c);
    knob->reading.d = !digitalRead(knob->pin.d);

    if (pValue != knob->reading.value)
    {
        Serial.print("knob: ");
        Serial.print(knob->reading.a);
        Serial.print(knob->reading.b);
        Serial.print(knob->reading.c);
        Serial.println(knob->reading.d);
    }
    pValue = knob->reading.value;
}

int32_t knob__getSelection(knob_t * knob)
{
    return knob->reading.value;
}