#include "RS485.h"
#include "modbusProtocol.h"
#include <Arduino.h>
#include "inputWrite.h"


void Forward (){
  uint8_t req [8];
  writeRegister(0x01, 0x0066, 0x0001, req);

  //TX transmission 
  rs485Tx();
  Serial1.write(req, 8);
  Serial1.flush();
  rs485Rx();
}

void Reverse (){
  uint8_t req [8];
  writeRegister(0x01, 0x0066, 0x0002, req);

  //TX transmission 
  rs485Tx();
  Serial1.write(req, 8);
  Serial1.flush();
  rs485Rx();
}

void Brake (){
  uint8_t req [8];
  writeRegister(0x01, 0x0066, 0x0003, req);

  //TX transmission 
  rs485Tx();
  Serial1.write(req, 8);
  Serial1.flush();
  rs485Rx();
}

void Speed (uint16_t dec){
  uint8_t req [8];
  writeRegister(0x01, 0x0056, dec, req);

  //TX transmission 
  rs485Tx();
  Serial1.write(req, 8);
  Serial1.flush();
  rs485Rx();
}

void InternalMode() {
  uint8_t req[8];

  // CHANGE THESE based on your manual
  const uint16_t REG_MODE = 0x0136;   // control source register
  const uint16_t MODE_INTERNAL = 0x0001; // internal / RS485 control

  writeRegister(0x01, REG_MODE, MODE_INTERNAL, req);

  rs485Tx();
  Serial1.write(req, 8);
  Serial1.flush();
  rs485Rx();
}
