#include "stopLight.hpp"
#include "Arduino.h"

void stopLight__clear(stopLight_t * stopLight)
{
    digitalWrite(stopLight->redPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_OFF);
    digitalWrite(stopLight->greenPin, LED_OFF);
}

void stopLight__setRed(stopLight_t * stopLight)
{
    digitalWrite(stopLight->greenPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_OFF);
    digitalWrite(stopLight->redPin, LED_ON);

}
void stopLight__setYellow(stopLight_t * stopLight)
{
    digitalWrite(stopLight->redPin, LED_OFF);
    digitalWrite(stopLight->greenPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_ON);
}
void stopLight__setGreen(stopLight_t * stopLight)
{
    digitalWrite(stopLight->redPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_OFF);
    digitalWrite(stopLight->greenPin, LED_ON);
}


void stopLight__update(stopLight_t * stopLight)
{
    
}

void stopLight__init(stopLight_t * stopLight)
{
    
}