#include "sevenSegmentDisplay.hpp"


void sevenSegmentDisplay__init(sevenSegmentDisplay_t * sevenSegmentDisplay)
{
    Wire.begin();
    Wire.setClock(I2C_FREQUENCY);

    sevenSegmentDisplay->displayDriver.begin();
    sevenSegmentDisplay->displayDriver.displayOn();
    sevenSegmentDisplay->displayDriver.displayClear();
}

void sevenSegmentDisplay__update(sevenSegmentDisplay_t * sevenSegmentDisplay)
{

}

void sevenSegementDisplay__displayValue(sevenSegmentDisplay_t * sevenSegmentDisplay, uint32_t value)
{
    sevenSegmentDisplay->displayDriver.displayInt(value);
}

void sevenSegmentDisplay__displayError(sevenSegmentDisplay_t * sevenSegmentDisplay)
{
    uint8_t error[] = {HT16K33_SPACE, HT16K33_E, HT16K33_R, HT16K33_R};
    sevenSegmentDisplay->displayDriver.display(error); 
}
