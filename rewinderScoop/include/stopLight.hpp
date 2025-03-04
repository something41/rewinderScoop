#include "stdint.h"

#define LED_OFF (HIGH)
#define LED_ON  (LOW)

typedef struct
{
    const uint32_t redPin;
    const uint32_t yellowPin;
    const uint32_t greenPin;
} stopLight_t;


void stopLight__clear(stopLight_t * stopLight);
void stopLight__setRed(stopLight_t * stopLight);
void stopLight__setYellow(stopLight_t * stopLight);
void stopLight__setGreen(stopLight_t * stopLight);

