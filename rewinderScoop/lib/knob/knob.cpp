#include "knob.hpp"
#include <Arduino.h>

static bool isWithinRange(int32_t test, int32_t min, int32_t max)
{
    if (test < min || test > max)
    {
        return false;
    }

    return true;
}

static uint32_t getSelectionFromRawReading(knob_t * knob)
{
    knob->rawReading = analogRead(knob->pin);

    uint32_t i = 0;

    for (i = 0; i < NUM_SELECTIONS; i++)
    {
        if (knob->rawReading > knob->thresholds[i])
        {
            break;
        }
    }

    return i;
}

void knob__init(knob_t * knob)
{
    knob->selection = getSelectionFromRawReading(knob);
}

int32_t knob__update(knob_t * knob)
{
    int32_t potentialSelection = getSelectionFromRawReading(knob);

    if (isWithinRange(potentialSelection, (knob->selection - 1), (knob->selection + 1)))
    {
        knob->selection = potentialSelection;
    }

    return knob->selection;

}

int32_t knob__getSelection(knob_t * knob)
{
    return (knob->selection);
}
