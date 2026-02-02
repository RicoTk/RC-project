#ifndef modbusProtocol_H
#define modbusProtocol_H
#include <Arduino.h>

//crc calculation 
uint16_t modbusCRC (const uint8_t* buf, uint8_t len);

#endif