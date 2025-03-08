#include "stopLight.hpp"
#include "Arduino.h"

#define LED_ERROR_DISPLAY_TIME_MS (100)

void stopLight__clear(stopLight_t * stopLight)
{
    digitalWrite(stopLight->redPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_OFF);
    digitalWrite(stopLight->greenPin, LED_OFF);
    stopLight->displayType = CLEAR;
}

void stopLight__setRed(stopLight_t * stopLight)
{
    digitalWrite(stopLight->greenPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_OFF);
    digitalWrite(stopLight->redPin, LED_ON);
    stopLight->displayType = RED;


}
void stopLight__setYellow(stopLight_t * stopLight)
{
    digitalWrite(stopLight->redPin, LED_OFF);
    digitalWrite(stopLight->greenPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_ON);
    stopLight->displayType = YELLOW;

}
void stopLight__setGreen(stopLight_t * stopLight)
{
    digitalWrite(stopLight->redPin, LED_OFF);
    digitalWrite(stopLight->yellowPin, LED_OFF);
    digitalWrite(stopLight->greenPin, LED_ON);
    stopLight->displayType = GREEN;

}


void stopLight__update(stopLight_t * stopLight)
{
    if (stopLight->showingError)
    {
        stopLight->errorCounter += 1;
        if (stopLight->errorCounter == LED_ERROR_DISPLAY_TIME_MS)
        {
            stopLight->errorCounter = 0;
            
            switch(stopLight->displayType)
            {
                case RED:
                case CLEAR:
                    stopLight__setYellow(stopLight);
                    break;
                case YELLOW:
                    stopLight__setGreen(stopLight);
                    break;
                case GREEN:
                    stopLight__setRed(stopLight);
                    break;
                default:
                    break;
            }
        }

    }
}

void stopLight__init(stopLight_t * stopLight)
{
    pinMode(stopLight->redPin, OUTPUT);
    pinMode(stopLight->yellowPin, OUTPUT);
    pinMode(stopLight->greenPin, OUTPUT);
}

void stopLight__error(stopLight_t * stopLight)
{
    stopLight->showingError = true;
}