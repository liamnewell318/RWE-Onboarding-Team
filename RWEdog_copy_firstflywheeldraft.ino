#include <IRremote.hpp>

const int AIN1 = 2;
const int AIN2 = 3;
const int BIN1 = 4;
const int BIN2 = 7;
const int PWMA = 5;
const int PWMB = 6;
const int STBY = 8;
const int IR_PIN = 9;

void setup() {
 Serial.begin(9600);

 pinMode(AIN1, OUTPUT);
 pinMode(AIN2, OUTPUT);
 pinMode(BIN1, OUTPUT);
 pinMode(BIN2, OUTPUT);
 pinMode(PWMA, OUTPUT);
 pinMode(PWMB, OUTPUT);
 pinMode(STBY, OUTPUT);

 digitalWrite(STBY, LOW);

 IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if(IrReceiver.decode()) {
    if(IrReceiver.decodedIRData.decodedRawData == 0xBA45FF00) {
      digitalWrite(STBY, !digitalRead(STBY));
    }
    IrReceiver.resume();
  }
  
  const int flyWheelSpeed = 50; //subject to change

  if (digitalRead(STBY) == HIGH) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMA, flyWheelSpeed);
    analogWrite(PWMB, flyWheelSpeed);
  }
  else {
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
  }
}