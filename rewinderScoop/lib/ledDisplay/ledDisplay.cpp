#include "ledDisplay.hpp"
#include "Arduino.h"

#define LED_ERROR_DISPLAY_TIME_MS (100)

static void clear(ledDisplay_t * ledDisplay)
{
    digitalWrite(ledDisplay->redPin, LED_OFF);
    digitalWrite(ledDisplay->yellowPin, LED_OFF);
    digitalWrite(ledDisplay->greenPin, LED_OFF);
}

static void setRed(ledDisplay_t * ledDisplay)
{
    digitalWrite(ledDisplay->greenPin, LED_OFF);
    digitalWrite(ledDisplay->yellowPin, LED_OFF);
    digitalWrite(ledDisplay->redPin, LED_ON);
}

static void setYellow(ledDisplay_t * ledDisplay)
{
    digitalWrite(ledDisplay->redPin, LED_OFF);
    digitalWrite(ledDisplay->greenPin, LED_OFF);
    digitalWrite(ledDisplay->yellowPin, LED_ON);
}

static void setGreen(ledDisplay_t * ledDisplay)
{
    digitalWrite(ledDisplay->redPin, LED_OFF);
    digitalWrite(ledDisplay->yellowPin, LED_OFF);
    digitalWrite(ledDisplay->greenPin, LED_ON);
}

static void processError(ledDisplay_t * ledDisplay)
{
    
    ledDisplay->error.counterMs += 1;

    if (ledDisplay->error.counterMs == LED_ERROR_DISPLAY_TIME_MS)
    {
        setYellow(ledDisplay);

    }
    else if (ledDisplay->error.counterMs == 2 * LED_ERROR_DISPLAY_TIME_MS)
    {
        setGreen(ledDisplay);

    }
    else if (ledDisplay->error.counterMs == 3 * LED_ERROR_DISPLAY_TIME_MS)
    {
        ledDisplay->error.counterMs = 0;
        setRed(ledDisplay);
    }
    
}
void ledDisplay__setClear(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = CLEAR;
}

void ledDisplay__setStop(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = STOP;
}
void ledDisplay__setSlow(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = SLOW;
}
void ledDisplay__setFast(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = FAST;
}

void ledDisplay__setError(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = ERROR;
}

void ledDisplay__update(ledDisplay_t * ledDisplay)
{
    switch(ledDisplay->displayType)
    {
        case CLEAR:
            clear(ledDisplay);
            break;
        case STOP:
            setRed(ledDisplay);
            break;
        case SLOW:
            setYellow(ledDisplay);
            break;
        case FAST:
            setGreen(ledDisplay);
            break;
        case ERROR:
            processError(ledDisplay);
            break;
        default:
            break;
    }
}

void ledDisplay__init(ledDisplay_t * ledDisplay)
{
    pinMode(ledDisplay->redPin, OUTPUT);
    pinMode(ledDisplay->yellowPin, OUTPUT);
    pinMode(ledDisplay->greenPin, OUTPUT);
}

