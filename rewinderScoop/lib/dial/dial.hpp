#include "Arduino.h"

typedef struct {
    uint32_t pin;
    uint32_t minValue;
    uint32_t maxValue;
    uint32_t rawReading;
    uint32_t cachedValue;
    float cachedValueFiltered;
    float rollingAverageFilterAmount;
    uint32_t minReadingValue;
    uint32_t maxReadingValue;
} dial_t;

#define DIAL_INIT(_pin, _minValue, _maxValue, _rollingAverageFilterAmount, _minReadingValue, _maxReadingValue) \
{ \
    .pin = _pin, \
    .minValue = _minValue, \
    .maxValue = _maxValue, \
    .rawReading = 0, \
    .cachedValue = 0, \
    .cachedValueFiltered = 0, \
    .rollingAverageFilterAmount = _rollingAverageFilterAmount, \
    .minReadingValue = _minReadingValue, \
    .maxReadingValue = _maxReadingValue, \
}

void dial__init(dial_t * dial);

uint32_t dial__update(dial_t * dial);

uint32_t dial__getRawReading(dial_t * dial);

uint32_t dial__getReading(dial_t * dial);