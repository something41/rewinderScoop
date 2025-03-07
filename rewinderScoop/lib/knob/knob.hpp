#include <Arduino.h>
#include <stdint.h>
#include <debounce.hpp>

#define MAX_VOLTAGE (5)

#define RESISTOR_0 0
#define RESISTOR_1 0
#define RESISTOR_2 0
#define RESISTOR_3 0
#define RESISTOR_4 0
#define RESISTOR_5 0
#define RESISTOR_6 0
#define RESISTOR_7 0
#define RESISTOR_8 0
#define RESISTOR_9 0
#define RESISTOR_10 0
#define RESISTOR_11 0

#define MAX_ADC_VAL (0b1111111111)


typedef struct
{
    const uint32_t pin;
    uint32_t currentReading;
    uint32_t previousReading;
    uint32_t thresholds[12];

} knob_t;

//todo math here
#define KNOB_INIT(_pin) { \
    .pin = _pin, \
    .currentReading = 0, \
    .previousReading = 0, \
    .thresholds = {0}, \
}

void knob__init(knob_t * knob);

uint32_t knob__update(knob_t * knob);

uint32_t knob__getSelection(knob_t * knob);