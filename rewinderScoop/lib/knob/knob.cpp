#include "knob.hpp"
#include <Arduino.h>

#define KNOB_TRANSITION_READING (60)

static uint32_t getSelectionFromReading(knob_t * knob)
{
    for (uint32_t i = 0; i < KNOB_NUM_VALUES; i++)
    {
        if (knob->rawReading < knob->thresholds[i])
        {
            return i;
        }
    }
    return KNOB_NUM_VALUES;
} 

void knob__init(knob_t * knob)
{
    knob->rawReading = analogRead(knob->pin);
    knob->selection = getSelectionFromReading(knob);


}
uint32_t t = 0;
uint32_t knob__update(knob_t * knob)
{
    knob->rawReading = analogRead(knob->pin);
    // if (t == 2000){
    //     Serial.println(knob->rawReading);
    //     t = 0;
    // }
    // t++;
 // Serial.println(knob->rawReading);
    if (knob->rawReading > KNOB_TRANSITION_READING)
    {
        knob->selection = getSelectionFromReading(knob);

        if (knob->selection != knob->previousSelection)
        {
            knob->previousSelection = knob->selection;
            Serial.println(knob->selection);
        //    Serial.print("  :  ");
        //    Serial.println(knob->rawReading);
        }

    }

    return knob->selection;
}

uint32_t knob__getSelection(knob_t * knob)
{
    return knob->selection;
}