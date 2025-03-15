#include <Arduino.h>
#include <stdint.h>
#include <debounce.hpp>

#define KNOB_MAX_VALUE (11)

typedef struct
{
    struct
    {
        const uint32_t a;
        const uint32_t b;
        const uint32_t c;
        const uint32_t d;
    } pin;

    union
    {
        struct
        {
            uint32_t a : 1;
            uint32_t b : 1;
            uint32_t c : 1;
            uint32_t d : 1;
        };
        uint32_t value;
    } reading;

} knob_t;

#define KNOB_INIT(_pinA, _pinB, _pinC, _pinD) \
{ \
    .pin = { \
        .a = _pinA, \
        .b = _pinB, \
        .c = _pinC, \
        .d = _pinD, \
    }, \
    .reading = { \
        .value = 0, \
    } \
}

void knob__init(knob_t * knob);

int32_t knob__update(knob_t * knob);

int32_t knob__getSelection(knob_t * knob);