#include <Arduino.h>
#include <stdint.h>
#include <debounce.hpp>

#ifndef KNOB_NUM_VALUES
#define KNOB_NUM_VALUES (11)
#endif

#define MIN_THRESHOLD ((72 + 78) / 2)
#define THRESHOLD_0   ((78 + 84) / 2)
#define THRESHOLD_1   ((84 + 92) / 2)
#define THRESHOLD_2   ((92 + 101) / 2)
#define THRESHOLD_3   ((101 + 112) / 2)
#define THRESHOLD_4   ((112 + 126) / 2)
#define THRESHOLD_5   ((126 + 145) / 2)
#define THRESHOLD_6   ((145 + 168) / 2)
#define THRESHOLD_7   ((168 + 202) / 2)
#define THRESHOLD_8   ((202 + 253) / 2)
#define THRESHOLD_9   ((253 + 338) / 2)
#define THRESHOLD_10  ((338 + 510) / 2)

#define KNOB_DEBOUNCE_TIME_MS (100)

typedef struct
{
    const uint32_t thresholds[KNOB_NUM_VALUES];
    uint32_t pin;
    uint32_t selection;
    uint32_t previousSelection;
    uint32_t rawReading;
    debounce_t debouncer;
} knob_t;

#define KNOB_INIT_FULL(_pin, _debounceTime, _threshold0,_threshold1, _threshold2, _threshold3, \
    _threshold4, _threshold5, _threshold6, _threshold7, _threshold8, _threshold9, _threshold10) \
{ \
    .thresholds = {_threshold0,_threshold1, _threshold2, _threshold3, \
        _threshold4, _threshold5, _threshold6, _threshold7, _threshold8, _threshold9, _threshold10}, \
    .pin = _pin, \
    .selection = 0, \
    .previousSelection = 0, \
    .rawReading = 0, \
    .debouncer = DEBOUNCE_INIT(_debounceTime) \
}

#define KNOB_INIT(_pin) KNOB_INIT_FULL(_pin, KNOB_DEBOUNCE_TIME_MS, THRESHOLD_0,THRESHOLD_1, THRESHOLD_2, THRESHOLD_3, \
    THRESHOLD_4, THRESHOLD_5, THRESHOLD_6, THRESHOLD_7, THRESHOLD_8, THRESHOLD_9, THRESHOLD_10)

void knob__init(knob_t * knob);

uint32_t knob__update(knob_t * knob);

uint32_t knob__getSelection(knob_t * knob);