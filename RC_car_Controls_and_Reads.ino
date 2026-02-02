#include "dataRead.h"
#include "inputWrite.h"
#include "RS485.h"
#include "modbusProtocol.h"
#include "motorControl.h"

void setup() {
  pinMode(RS485_DE, OUTPUT);
  pinMode(RS485_RE, OUTPUT);

  Serial.begin(115200);
  Serial1.begin(9600);

  rs485Rx();
  delay(300);

  InternalMode();   // 0x0136 = 1
  delay(50);

  Speed(1000);      // 0x0056 = 2000
  delay(50);

  Forward(); 
}

void loop() {

}




