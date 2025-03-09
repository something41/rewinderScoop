#include "Arduino.h"

typedef struct {
    uint32_t pin;
    uint32_t scale;
    uint32_t rawReading;
} dial_t;

#define DIAL_INIT(_pin, _scale) { \
    .pin = _pin, \
    .scale = _scale, \
    .rawReading = 0, \
}

void dial__init(dial_t * dial);

uint32_t dial__update(dial_t * dial);

uint32_t dial__getRawReading(dial_t * dial);

uint32_t dial__getReading(dial_t * dial);