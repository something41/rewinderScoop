#include "stopLight.hpp"
#include "Arduino.h"

#define HALF_SECOND_IN_MS (500)

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
    if (stopLight->showingError)
    {
        if (stopLight->errorCounter++)
        {
            stopLight->errorCounter = 0;
            
            if(digitalRead(stopLight->redPin))
            {
                stopLight__setYellow(stopLight);
            }
            else if(digitalRead(stopLight->yellowPin))
            {
                stopLight__setGreen(stopLight);
            }
            else{
                stopLight__setRed(stopLight);
            }
        }

    }
}

void stopLight__init(stopLight_t * stopLight)
{
    
}

void stopLight__error(stopLight_t * stopLight)
{
    stopLight->showingError = true;
}