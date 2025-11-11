#include <Servo.h>


const int PG = 9; 
const int ALM = 7;
const int SV = 3;
const int EN = 2;
const int F_R = 4;
const int BK = 5;
const int Servo = 10;

const byte PIN_PG = 21;           // use an interrupt-capable pin
const float PULSES_PER_REV = 24; // set to your motor/driver value

volatile unsigned long pgCount = 0;

void onPG() {
  pgCount++;
}

void motor_forward (string motor_driver = LOW, string direction = LOW, string brake = LOW, int speed = 255){
    // Enable motor driver (LOW to enable)
  digitalWrite(EN, motor_driver);

  // Set direction (LOW for forward, HIGH for reverse)
  digitalWrite(F_R, direction);  // Forward direction

  // Disable brake (HIGH to disable break)
  digitalWrite(BK, brake); 

  // Set PWM speed (0 to 255)
  analogWrite(SV, speed );  // Full speed to test

}

void motor_reverse (string motor_driver = LOW, string direction = HIGH, string brake = LOW, int speed = 255){
    // Enable motor driver (LOW to enable)
  digitalWrite(EN, motor_driver);

  // Set direction (LOW for forward, HIGH for reverse)
  digitalWrite(F_R, direction);  // Forward direction

  // Disable brake (HIGH to disable break)
  digitalWrite(BK, brake); 

  // Set PWM speed (0 to 255)
  analogWrite(SV, speed );  // Full speed to test

}

void motor_stop (string motor_driver = HIGH, string direction = LOW, string brake = HIGH, int speed = 0){
    // Enable motor driver (LOW to enable)
  digitalWrite(EN, motor_driver);

  // Set direction (LOW for forward, HIGH for reverse)
  digitalWrite(F_R, direction);  // Forward direction

  // Disable brake (HIGH to disable break)
  digitalWrite(BK, brake); 

  // Set PWM speed (0 to 255)
  analogWrite(SV, speed );  // Full speed to test

}

void speed_calc (unsigned long startCount, unsigned long endCount){
  unsigned long pulses = endCount - startCount;
  float revs = pulses / PULSES_PER_REV;
  float rpm  = (revs * 60000.0) / sample_ms;

  Serial.print("Pulses: "); Serial.print(pulses);
  Serial.print("  RPM: ");  Serial.println(rpm);
}

void servoControl (int steeringAngle){
  myServo.write(steeringAngle);
}

void setup() {
  // Set pin modes
  pinMode(PIN_PG, INPUT_PULLUP);
  pinMode(ALM, INPUT);
  pinMode(SV, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(F_R, OUTPUT);
  pinMode(BK, OUTPUT);
  myServo.attach(9);

  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(PIN_PG), onPG, RISING);
}

double speed = analogRead(PG);

void loop() {
  
  servoControl();
  motor_forward();

  const unsigned long sample_ms = 1000;     // 1 second window
  unsigned long start = millis();
  unsigned long startCount;

  noInterrupts();
  startCount = pgCount;
  interrupts();

  delay(sample_ms);

  noInterrupts();
  unsigned long endCount = pgCount;
  interrupts();

  speed_calc();



  