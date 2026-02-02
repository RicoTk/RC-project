#ifndef INPUTWRITE_H
#define INPUTWRITE_H

#include <Arduino.h>   // for uint8_t, uint16_t

bool writeRegister(uint8_t slave, uint16_t reg, uint16_t outVal, uint8_t req[8]);

#endif // INPUTWRITE_H