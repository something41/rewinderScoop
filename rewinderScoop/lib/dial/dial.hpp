#include "Arduino.h"

typedef struct {
    uint32_t pin;
    uint32_t minValue;
    uint32_t maxValue;
    uint32_t rawReading;
    uint32_t resolution;
    uint32_t maxRawValue;
    uint32_t cachedValue;
} dial_t;

#define DIAL_INIT(_pin, _minValue, _maxValue, _resolution) { \
    .pin = _pin, \
    .minValue = _minValue, \
    .maxValue = _maxValue, \
    .rawReading = 0, \
    .resolution = _resolution, \
    .maxRawValue = (1 << _resolution) - 1, \
    .cachedValue = 0, \
}

void dial__init(dial_t * dial);

uint32_t dial__update(dial_t * dial);

uint32_t dial__getRawReading(dial_t * dial);

uint32_t dial__getReading(dial_t * dial);