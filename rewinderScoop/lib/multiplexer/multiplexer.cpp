#include <Arduino.h>
#include "multiplexer.hpp"

#define CHANNEL_SWITCH_DELAY_uS (1)

void enableSelector(multiplexer_t * multiplexer)
{
    digitalWrite(multiplexer->selectPins[0], multiplexer->select0);
    digitalWrite(multiplexer->selectPins[1], multiplexer->select1);
    digitalWrite(multiplexer->selectPins[2], multiplexer->select2);
    delayMicroseconds(CHANNEL_SWITCH_DELAY_uS);
}

void multiplexer__init(multiplexer_t * multiplexer)
{

}

void multiplexer__update(multiplexer_t * multiplexer)
{
    for(selectionIndex_t index = 0; index < multiplexer->numChannels; index++)
    {
        enableSelector(multiplexer);
        multiplexer->cachedValues[i].raw = analogRead(multiplexer->ioPin);
    }
}


void multiplexer__getCachedReadOfChannel(multiplexer_t * multiplexer, uint32_t channel)
{

}

uint32_t multiplexer__getCachedReadOfChannelRaw(multiplexer_t * multiplexer, uint32_t channel)
{

}

uint32_t multiplexer__getReadOfChannel(multiplexer_t * multiplexer, uint32_t channel)
{

}

uint32_t multiplexer__getReadOfChannelRaw(multiplexer_t * multiplexer, uint32_t channel)
{

}


