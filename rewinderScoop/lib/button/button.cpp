#include "button.hpp"



bool button__update(button_t * button)
{
    bool sampledValue = digitalRead(button->pin);
    uint32_t timer = millis();

    if (sampledValue != button->previousStatus)
    {
        button->startTime = timer;
    }

    button->previousStatus = sampledValue;

    if (timer - button->startTime  > button->debounceTimeMs)
    {
        if (sampledValue != button->status)
        {
            button->status = sampledValue;
            return true;
        }
    }

    return false;
}

bool button__getStatus(button_t * button)
{
    return button->status;
}

void button__init(button_t * button)
{
    button->previousStatus = false;
    button->status = false;
    button->startTime = 0;
}

