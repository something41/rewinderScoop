#include "Arduino.h"
#include "debounce.hpp"

#define UNUSED_PIN (UINT32_MAX)

typedef enum
{
    ENOCDER_MODE_A = 0,
    ENCODER_MODE_AB,
    ENCODER_MODE_ABZ,
    ENCODER_MODE_Z,
} encoder_mode_t;

typedef enum
{
    DIRECTION__POSITIVE = 1,
    DIRECTION__NEGATIVE = -1,
    DIRECTION__UNKNOWN  = 0,
} encoder_direction_t;

typedef enum
{
    RUN_MODE_DISABLE = 0,
    RUN_MODE_ENABLE = 1,
} encoder_run_mode_t;

typedef struct
{
    const encoder_mode_t mode;
    encoder_run_mode_t runMode;
    encoder_direction_t direction;
    uint32_t totalCounter;
    debounce_t debounceError;

    struct
    {
        uint32_t a;
        uint32_t b;
        uint32_t z;
    } pin;

    struct
    {
        uint32_t a;
        uint32_t b;
        uint32_t z;
    } countOf;

    struct
    {
        uint32_t ab;
        uint32_t z;
    } scaleInFeet;

} abzEncoder_t;


#define ENCODER_INIT(_pinA, _pinB, _pinZ, _scaleAB, _scaleZ, _mode, _debounceTimeMs) \
{ \
    .mode = _mode, \
    .runMode =RUN_MODE_DISABLE, \
    .direction = DIRECTION__UNKNOWN, \
    .totalCounter = 0, \
    .debounceError = DEBOUNCE_INIT(_debounceTimeMs), \
    .pin = { \
        .a = _pinA, \
        .b = _pinB, \
        .z = _pinZ, \
    }, \
    .countOf = { \
        .a = 0, \
        .b = 0, \
        .z = 0, \
    }, \
    .scaleInFeet { \
    .ab = _scaleAB, \
    .z = _scaleZ, \
    } \
}

#define ENCODER_INIT_ABZ(_pinA, _pinB, _pinZ, _scaleAB, _scaleZ, _mode, _debounceTimeMs) ENCODER_INIT(_pinA, _pinB, _pinZ, _scaleAB, _scaleZ, ENCODER_MODE_ABZ, _debounceTimeMs)

#define ENCODER_INIT_AB(_pinA, _pinB, _scaleAB, _debounceTimeMs) ENCODER_INIT(_pinA, _pinB, UNUSED_PIN, _scaleAB, 0, ENCODER_MODE_AB, _debounceTimeMs)

#define ENCODER_INIT_Z(_pinZ, _scaleZ, _debounceTimeMs) ENCODER_INIT(UNUSED_PIN, UNUSED_PIN, _pinZ, 0, _scaleZ, ENCODER_MODE_Z, _debounceTimeMs)

void abzEncoder__init(abzEncoder_t * encoder);

void abzEncoder__update(abzEncoder_t * encoder);

uint32_t abzEncoder__getValue(abzEncoder_t * encoder);

void abzEncoder__reset(abzEncoder_t * encoder);

encoder_direction_t abzEncoder__getDirection(abzEncoder_t * encoder);


bool abzEncoder__stallErrorDetected(abzEncoder_t * encoder);