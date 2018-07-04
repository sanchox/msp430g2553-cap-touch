#include "structure.h"

#define ELEMENT(_number_, _port_, _bit_, _mr_, _tr_)\
const struct Element element_##_number_ = {\
    .inputPxselRegister = (unsigned char *)&P##_port_##SEL,\
    .inputPxsel2Register = (unsigned char *)&P##_port_##SEL2,\
    .inputBits = BIT##_bit_,\
    .maxResponse = _mr_,\
    .threshold = _tr_ }

// Wheel
ELEMENT(1, 1, 3, 1655, 1000);
ELEMENT(2, 1, 4, 1655, 1000);
ELEMENT(3, 1, 5, 1655, 1000);
ELEMENT(4, 2, 0, 1655, 1000);
ELEMENT(5, 2, 1, 1655, 1000);
ELEMENT(6, 2, 2, 1655, 1000);
ELEMENT(7, 2, 3, 1655, 1000);
ELEMENT(8, 2, 4, 1655, 1000);
// Center
ELEMENT(9, 2, 5, 1655, 1000);


//*** CAP TOUCH HANDLER *******************************************************/
// This defines the grouping of sensors, the method to measure change in
// capacitance, and the function of the group

const struct Sensor plane =
{
    .halDefinition = RO_PINOSC_TA0_WDTp,
    .numElements = 9,
    .baseOffset = 0,
    // Pointer to elements
    .arrayPtr[0] = &element_1,
    .arrayPtr[1] = &element_2,
    .arrayPtr[2] = &element_3,
    .arrayPtr[3] = &element_4,
    .arrayPtr[4] = &element_5,
    .arrayPtr[5] = &element_6,
    .arrayPtr[6] = &element_7,
    .arrayPtr[7] = &element_8,
    .arrayPtr[8] = &element_9,
    // Timer Information
    .measGateSource = GATE_WDTp_SMCLK,
    .accumulationCycles = WDTp_GATE_32768,
};

//PinOsc Wheel
const struct Sensor wheel =
{
    .halDefinition = RO_PINOSC_TA0_WDTp,
    .numElements = 8,
    .baseOffset = 9,
    // Pointer to elements
    .arrayPtr[0] = &element_1,
    .arrayPtr[1] = &element_2,
    .arrayPtr[2] = &element_3,
    .arrayPtr[3] = &element_4,
    .arrayPtr[4] = &element_5,
    .arrayPtr[5] = &element_6,
    .arrayPtr[6] = &element_7,
    .arrayPtr[7] = &element_8,
    // Timer Information
    .measGateSource = GATE_WDTp_SMCLK,
    .accumulationCycles = WDTp_GATE_32768,
    .points = 255,
    .sensorThreshold = 15,
};

//PinOsc Slider
const struct Sensor horisontal_slider =
{
    .halDefinition = RO_PINOSC_TA0_WDTp,
    .numElements = 3,
    .baseOffset = 17,
    // Pointer to elements
    .arrayPtr[0] = &element_8,
    .arrayPtr[1] = &element_9,
    .arrayPtr[2] = &element_4,
    // Timer Information
    .measGateSource = GATE_WDTp_SMCLK,
    .accumulationCycles = WDTp_GATE_32768,
    .points = 255,
    .sensorThreshold = 15,
};

//PinOsc Slider
const struct Sensor vertical_slider =
{
     .halDefinition = RO_PINOSC_TA0_WDTp,
     .numElements = 3,
     .baseOffset = 20,
     // Pointer to elements
     .arrayPtr[0] = &element_6,
     .arrayPtr[1] = &element_9,
     .arrayPtr[2] = &element_2,
     // Timer Information
     .measGateSource = GATE_WDTp_SMCLK,
     .accumulationCycles = WDTp_GATE_32768,
     .points = 255,
     .sensorThreshold = 15,
};

