#include <Arduino.h>
#include "RS485.h"


// =======================
// RS-485 helper functions
// =======================
// Put the MAX485 into transmit mode so bytes go onto the A/B bus.
void rs485Tx() {
  digitalWrite(RS485_DE, HIGH);   // enable driver (transmit)
  digitalWrite(RS485_RE, HIGH);   // disable receiver during TX (prevents echo/noise)
  delayMicroseconds(10);          // small settle time for the transceiver
}

// Put the MAX485 into receive mode so RO outputs incoming bytes to the Arduino RX pin.
void rs485Rx() {
  digitalWrite(RS485_DE, LOW);    // disable driver (stop transmitting)
  digitalWrite(RS485_RE, LOW);    // enable receiver
  delayMicroseconds(10);          // small settle time
}