#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

void Forward();
void Reverse();
void Brake();
void Speed(uint16_t dec);
void InternalMode();

#endif
