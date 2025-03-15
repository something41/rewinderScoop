#include "button.hpp"

void button__init(button_t * button)
{
    pinMode(button->pin, INPUT_PULLUP);
    debounce__init(&button->debounce);
}

bool button__update(button_t * button)
{
    bool sampledValue = !digitalRead(button->pin);
    if (button->isInverted)
    {
        sampledValue = !sampledValue;
    }
    return debounce__update(&button->debounce, sampledValue);
}

bool button__getStatus(button_t * button)
{   
    //active low just invert 
    return debounce__getStatus(&button->debounce);
}