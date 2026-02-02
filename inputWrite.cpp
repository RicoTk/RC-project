#include "modbusProtocol.h"
#include "RS485.h"
#include "inputWrite.h"
#include <Arduino.h>

bool writeRegister(uint8_t slave, uint16_t reg, uint16_t outVal, uint8_t req[8]) {
  req[0] = slave;
  req[1] = 0x06;
  req[2] = (reg >> 8) & 0xFF;
  req[3] = reg & 0xFF;
  req[4] = (outVal >> 8) & 0xFF;
  req[5] = outVal & 0xFF;

  uint16_t crc = modbusCRC(req, 6);
  req[6] = crc & 0xFF;
  req[7] = (crc >> 8) & 0xFF;

  while (Serial1.available()) Serial1.read();

  return true;
}




