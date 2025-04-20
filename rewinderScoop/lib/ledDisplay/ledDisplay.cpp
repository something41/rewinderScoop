#include "ledDisplay.hpp"
#include "Arduino.h"

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
    ledDisplay->counterMs += 1;

    if (ledDisplay->counterMs == LED_ERROR_DISPLAY_TIME_MS)
    {
        setYellow(ledDisplay);
    }
    else if (ledDisplay->counterMs == 2 * LED_ERROR_DISPLAY_TIME_MS)
    {
        setGreen(ledDisplay);
    }
    else if (ledDisplay->counterMs == 3 * LED_ERROR_DISPLAY_TIME_MS)
    {
        ledDisplay->counterMs = 0;
        setRed(ledDisplay);
    }
}

static void processFinish(ledDisplay_t * ledDisplay)
{
    ledDisplay->counterMs += 1;

    if (ledDisplay->counterMs == LED_ERROR_DISPLAY_TIME_MS)
    {
        clear(ledDisplay);
    }
    else if (ledDisplay->counterMs == 2 * LED_ERROR_DISPLAY_TIME_MS)
    {
        setRed(ledDisplay);
    }
    else if (ledDisplay->counterMs == 3 * LED_ERROR_DISPLAY_TIME_MS)
    {
        clear(ledDisplay);
    }
    else if (ledDisplay->counterMs == 4 * LED_ERROR_DISPLAY_TIME_MS)
    {
        setRed(ledDisplay);
    }
    else if (ledDisplay->counterMs > 4 * LED_ERROR_DISPLAY_TIME_MS)
    {
        ledDisplay->counterMs = 0;
        ledDisplay->isDone = true;
    }
    
}
void ledDisplay__setClear(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = DISPLAY_TYPE__CLEAR;
}

void ledDisplay__setStop(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = DISPLAY_TYPE__STOP;
}
void ledDisplay__setSlow(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = DISPLAY_TYPE__SLOW;
}
void ledDisplay__setFast(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = DISPLAY_TYPE__FAST;
}

void ledDisplay__setError(ledDisplay_t * ledDisplay)
{
    ledDisplay->displayType = DISPLAY_TYPE__ERROR;
}

void ledDisplay__setFinish(ledDisplay_t * ledDisplay)
{
    ledDisplay->counterMs = 0;
    ledDisplay->isDone = false;
    ledDisplay->displayType = DISPLAY_TYPE__FINISH;
}

bool ledDisplay__isDone(ledDisplay_t * ledDisplay)
{
    return ledDisplay->isDone;
}

void ledDisplay__update(ledDisplay_t * ledDisplay)
{
    switch(ledDisplay->displayType)
    {
        case DISPLAY_TYPE__CLEAR:
            clear(ledDisplay);
            break;
        case DISPLAY_TYPE__STOP:
            setRed(ledDisplay);
            break;
        case DISPLAY_TYPE__SLOW:
            setYellow(ledDisplay);
            break;
        case DISPLAY_TYPE__FAST:
            setGreen(ledDisplay);
            break;
        case DISPLAY_TYPE__FINISH:
            processFinish(ledDisplay);
            break;
        case DISPLAY_TYPE__ERROR:
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

