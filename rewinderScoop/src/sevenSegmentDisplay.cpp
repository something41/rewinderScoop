#include "sevenSegmentDisplay.hpp"


void sevenSegmentDisplay__init(sevenSegmentDisplay_t * sevenSegmentDisplay)
{
    Wire.begin();
    Wire.setClock(I2C_FREQUENCY);

    sevenSegmentDisplay->displayDriver.begin();
    sevenSegmentDisplay->displayDriver.displayOn();
}

void sevenSegmentDisplay__update(sevenSegmentDisplay_t * sevenSegmentDisplay)
{
    sevenSegementDisplay__displayValue(sevenSegmentDisplay, 1234);
}

void sevenSegementDisplay__displayValue(sevenSegmentDisplay_t * sevenSegmentDisplay, uint32_t value)
{
    sevenSegmentDisplay->displayDriver.displayInt(value);
}
