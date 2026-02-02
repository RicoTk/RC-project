#include "RS485.h"
#include "modbusProtocol.h"
#include "dataRead.h"
#include <Arduino.h>

// ----- Configuration (keep these in ONE place) -----
static const uint8_t  SLAVE_ID = 0x01;
static const uint16_t REG_ACTUAL_CURRENT = 0x00B6;
static const float    CURRENT_SCALE = 25.0f;     // raw/25 = amps (based on your comment)
static const uint16_t POLL_MS = 300;

// ----- Internal state (private to this module) -----
static uint32_t lastPollMs = 0;
static bool     haveCurrent = false;
static uint16_t currentRaw = 0;
static float    currentA = 0.0f;

static DataReadError lastErr = DataReadError::None;

// ----- Internal helper: read 1 register (your function, lightly improved) -----
bool readHoldingRegister(uint8_t slave, uint16_t reg, uint16_t &outVal, uint16_t timeoutMs = 120) {

  // Build request
  uint8_t req[8];
  req[0] = slave;
  req[1] = 0x03;               
  req[2] = (reg >> 8) & 0xFF;
  req[3] = reg & 0xFF;
  req[4] = 0x00;
  req[5] = 0x01;

  uint16_t crc = modbusCRC(req, 6);
  req[6] = crc & 0xFF;
  req[7] = (crc >> 8) & 0xFF;

  // Clear RX buffer
  while (Serial1.available()) Serial1.read();

  // Send
  rs485Tx();
  Serial1.write(req, 8);
  Serial1.flush();
  rs485Rx();

  // Receive (expect 7 bytes for 1 register)
  uint8_t resp[7];
  uint8_t idx = 0;
  uint32_t t0 = millis();

  while ((millis() - t0) < timeoutMs && idx < sizeof(resp)) {
    if (Serial1.available()) resp[idx++] = Serial1.read();
  }

  if (idx != sizeof(resp)) { lastErr = DataReadError::TimeoutOrShortFrame; return false; }
  if (resp[0] != slave)     { lastErr = DataReadError::BadSlave; return false; }

  if (resp[1] == (0x03 | 0x80)) { lastErr = DataReadError::ExceptionResponse; return false; }
  if (resp[1] != 0x03)          { lastErr = DataReadError::BadFunction; return false; }
  if (resp[2] != 0x02)          { lastErr = DataReadError::BadByteCount; return false; }

  uint16_t crcCalc = modbusCRC(resp, 5);
  uint16_t crcRecv = resp[5] | (uint16_t(resp[6]) << 8);
  if (crcCalc != crcRecv) { lastErr = DataReadError::BadCRC; return false; }

  outVal = (uint16_t(resp[3]) << 8) | resp[4];
  lastErr = DataReadError::None;
  return true;
}

// ----- Public API -----
void dataRead_init() {
  lastPollMs = 0;
  haveCurrent = false;
  currentRaw = 0;
  currentA = 0.0f;
  lastErr = DataReadError::None;
}

void dataRead_update() {
  uint32_t now = millis();
  if (now - lastPollMs < POLL_MS) return;   // rate limit polling
  lastPollMs = now;

  uint16_t raw;
  if (readHoldingRegister(SLAVE_ID, REG_ACTUAL_CURRENT, raw)) {
    currentRaw = raw;
    currentA = raw / CURRENT_SCALE;
    haveCurrent = true;
  } else {
    // keep last good value; just mark "no new valid sample this cycle" if you want
    // haveCurrent stays true if you already had a valid reading previously
  }
}

bool dataRead_hasCurrent() {
  return haveCurrent;
}

float dataRead_getCurrentA() {
  return currentA;
}

uint16_t dataRead_getCurrentRaw() {
  return currentRaw;
}

DataReadError dataRead_lastError() {
  return lastErr;
}
