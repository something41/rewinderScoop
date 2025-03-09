#include <Arduino.h>
#include <stdint.h>
#include <debounce.hpp>


#define THRESHOLD_0 922
#define THRESHOLD_1 685
#define THRESHOLD_2 480
#define THRESHOLD_3 370
#define THRESHOLD_4 305
#define THRESHOLD_5 260
#define THRESHOLD_6 226
#define THRESHOLD_7 200
#define THRESHOLD_8 180
#define THRESHOLD_9 165
#define THRESHOLD_10 151
#define THRESHOLD_11 72

#define NUM_SELECTIONS (11)


typedef struct
{
    const uint32_t pin;
    uint32_t rawReading;
    int32_t selection;
    const uint32_t thresholds[12];

} knob_t;

#define KNOB_INIT(_pin, _threshold0, _threshold1, _threshold2, _threshold3, _threshold4, \
                    _threshold5, _threshold6, _threshold7, _threshold8, _threshold9, \
                    _threshold10, _threshold11) { \
    .pin = _pin, \
    .rawReading = 0, \
    .selection = 0, \
    .thresholds = {_threshold0, _threshold1, _threshold2, _threshold3, _threshold4, _threshold5, \
                    _threshold6, _threshold7, _threshold8, _threshold9, _threshold10, _threshold11} \
}

#define KNOB_DEFAULT_INIT(_pin) KNOB_INIT(_pin, THRESHOLD_0, THRESHOLD_1, THRESHOLD_2, THRESHOLD_3, \
                                                THRESHOLD_4, THRESHOLD_5, THRESHOLD_6, THRESHOLD_7, THRESHOLD_8, \
                                                THRESHOLD_9, THRESHOLD_10, THRESHOLD_11)
void knob__init(knob_t * knob);

int32_t knob__update(knob_t * knob);

int32_t knob__getSelection(knob_t * knob);