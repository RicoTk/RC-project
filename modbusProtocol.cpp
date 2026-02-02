//
//#include <algorithm>
#include <Arduino.h>

//crc calculation 

// =======================
// Modbus RTU CRC-16
// =======================
// Modbus RTU frames end with a 16-bit CRC (2 bytes).
// This function computes CRC-16(Modbus):
// - init = 0xFFFF
// - poly = 0xA001
// - bit order = LSB-first
//
// You compute CRC over all frame bytes EXCEPT the CRC bytes themselves.
uint16_t modbusCRC(const uint8_t* buf, uint8_t len) {
  uint16_t crc = 0xFFFF;          // Modbus requires starting at 0xFFFF

  for (uint8_t i = 0; i < len; i++) {
    crc ^= buf[i];                // XOR next data byte into low byte of CRC

    // Process 8 bits, LSB first
    for (uint8_t b = 0; b < 8; b++) {
      if (crc & 0x0001) {          // if LSB is 1
        crc = (crc >> 1) ^ 0xA001; // shift and XOR polynomial
      } else {
        crc >>= 1;                // just shift
      }
    }
  }
  return crc;                      // final 16-bit CRC value
}