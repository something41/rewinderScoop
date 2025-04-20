#include "knob.hpp"
#include <Arduino.h>
#include "debounce.hpp"

static uint32_t getSelectionFromReading(knob_t * knob)
{
    if (knob->rawReading < MIN_THRESHOLD)
    {
        return KNOB_NUM_VALUES;
    }

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
    debounce__init(&knob->debouncer);
}

uint32_t knob__update(knob_t * knob)
{
    knob->rawReading = analogRead(knob->pin);

    uint32_t tempSelection = getSelectionFromReading(knob);
    
    if (debounce__update(&knob->debouncer, tempSelection))
    {
        knob->selection = debounce__getStatus(&knob->debouncer);
        if (knob->selection != knob->previousSelection)
        {
            knob->previousSelection = knob->selection;
        }
    }

    return knob->selection;
}

uint32_t knob__getSelection(knob_t * knob)
{
    return knob->selection;
}