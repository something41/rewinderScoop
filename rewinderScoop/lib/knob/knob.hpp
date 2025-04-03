#include <Arduino.h>
#include <stdint.h>
#include <debounce.hpp>

#ifndef KNOB_NUM_VALUES
#define KNOB_NUM_VALUES (11)
#endif

#define MIN_THRESHOLD (80)
#define THRESHOLD_0   (160)
#define THRESHOLD_1   (240)
#define THRESHOLD_2   (300)
#define THRESHOLD_3   (370)
#define THRESHOLD_4   (445)
#define THRESHOLD_5   (525)
#define THRESHOLD_6   (580)
#define THRESHOLD_7   (650)
#define THRESHOLD_8   (760)
#define THRESHOLD_9   (820)
#define THRESHOLD_10  (900)

#define KNOB_DEBOUNCE_TIME_MS (250)

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