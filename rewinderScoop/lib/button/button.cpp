#include "button.hpp"

bool button__update(button_t * button)
{
    bool sampledValue = digitalRead(button->pin);
    return debounce__update(&button->debounce, sampledValue);
}

bool button__getStatus(button_t * button)
{
    return debounce__getStatus(&button->debounce);
}

void button__init(button_t * button)
{
    //pinMode(button->pin, INPUT_PULLUP);
    debounce__init(&button->debounce);
}

