#include "HT16K33.h"

#define I2C_FREQUENCY (100000)
#define DEFAULT_I2C_ADDRESS (0x70)

typedef enum {
    BLANK,
    COUNT_DOWN,
    COUNT_UP,
    SET,
} displayMode_t;

typedef struct {
    HT16K33 displayDriver;
    displayMode_t mode;
    uint32_t currentValue;
    uint32_t endPoint;
    
} sevenSegmentDisplay_t;

#define SEVEN_SEGMENT_DISPLAY_INIT(_address) \
{ \
    .displayDriver = {_address}, \
    .mode = BLANK, \
    .currentValue = 0, \
    .endPoint = 0, \
}


void sevenSegmentDisplay__init(sevenSegmentDisplay_t * sevenSegmentDisplay);

void sevenSegmentDisplay__update(sevenSegmentDisplay_t * sevenSegmentDisplay);

void sevenSegmentDisplay__displayValue(sevenSegmentDisplay_t * sevenSegmentDisplay, uint32_t value);

void sevenSegmentDisplay__displayError(sevenSegmentDisplay_t * sevenSegmentDisplay);
