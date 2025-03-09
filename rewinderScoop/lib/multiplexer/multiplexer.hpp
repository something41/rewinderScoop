#include <Arduino.h>

#define NUM_CHANNELS (8)
#define NUM_SELECTOR_PINS (3)

typedef enum {
    ANALOG,
    DIGITAL_INPUT,
    DIGITAL_OUTPUT,
} output_type_t;

typedef union
{
    struct
    {
        bool select0 : 1;
        bool select1 : 1;
        bool select2 : 1;
    };
    uint32_t index;
} selectionIndex_t;

typedef struct {
    union {
        uint32_t threshold; // only used if its digital
        uint32_t scale;     // if its analog, we could scale it here
    };
    const output_type_t type;
    uint32_t raw;

} io_t;

typedef struct {
    uint32_t ioPin;
    uint32_t selectPins[NUM_SELECTOR_PINS];
    uint32_t numChannels;

    io_t cachedValues[NUM_CHANNELS];
} multiplexer_t;

/*todo define thresholds */
#define INIT_DIGITAL_INPUT { \
    .threshold = 0, \
    .type = DIGITAL_INPUT, \
    .raw = 0, \
}

#define INIT_DIGITAL_OUTPUT { \
    .threshold = 0, \
    .type = DIGITAL_OUTPUT, \
    .raw = 0, \
}

#define INIT_ANALOG_INPUT(_scale) { \
        .scale = 1, \
    .type = ANALOG, \
    .raw = 0, \
}

#define INIT_ANALOG_INPUT_RAW INIT_ANALOG_INPUT(1)