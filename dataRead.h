#ifndef dataRead_H
#define dataRead_H

#include <Arduino.h>

// Call once in setup()
void dataRead_init();

// Call repeatedly in loop() (polls at a fixed interval internally)
void dataRead_update();

// Read-only getters for the rest of your program
bool  dataRead_hasCurrent();          // do we have a valid current reading yet?
float dataRead_getCurrentA();         // latest current in amps
uint16_t dataRead_getCurrentRaw();    // latest raw register value


// Put the enum in the header so everyone sees the type
enum class DataReadError : uint8_t {
  None = 0,
  TimeoutOrShortFrame,
  BadSlave,
  ExceptionResponse,
  BadFunction,
  BadByteCount,
  BadCRC
};

DataReadError dataRead_lastError();

#endif