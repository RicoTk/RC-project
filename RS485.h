#ifndef RS485_H
#define RS485_H

#include <Arduino.h>

static const uint8_t RS485_DE = 4;
static const uint8_t RS485_RE = 3;

void rs485Tx();
void rs485Rx();

#endif
