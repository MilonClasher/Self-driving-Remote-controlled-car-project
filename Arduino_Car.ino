#include <IRremote.hpp>
const int STBY = 9;
int IR_PIN = 11;
uint32_t hexCode;

// Replace these with actual codes from your remote
const uint32_t forwardOnCode = 0x9F600707;
const uint32_t backwardOnCode = 0x9E610707;
const uint32_t leftOnCode = 0x9A650707;
const uint32_t rightOnCode = 0x9D620707;

const uint32_t SpeedControl1 = 0xB9460707;
const uint32_t SpeedControl2 = 0x936C0707;
const uint32_t SpeedControl3 = 0xEB140707;
const uint32_t SpeedControl4 = 0xEA150707;
const uint32_t SpeedControl5 = 0xE9160707;

// Motor A
const int pwmA = 5;
const int in1A = 3;
const int in2A = 4;

// Motor B
const int pwmB = 6;
const int in1B = 7;
const int in2B = 8;

// Speed levels
const int speed0 = 0;
const int speed1 = 64;
const int speed2 = 128;
const int speed3 = 192;
const int speed4 = 255;

void setup() {
  IrReceiver.begin(IR_PIN);
  Serial.begin(9600);

  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);

  analogWrite(pwmA, speed2);
  analogWrite(pwmB, speed2);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
}

void loop() {
  if (IrReceiver.decode()) {
    hexCode = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("IR code: 0x");
    Serial.println(hexCode, HEX);

    switch (hexCode) {
      case forwardOnCode:
       Serial.println("Gone forward");
        digitalWrite(in1A, HIGH);
        digitalWrite(in2A, LOW);
        digitalWrite(in1B, HIGH);
        digitalWrite(in2B, LOW);
        break;

      case backwardOnCode:
      Serial.println("Gone backward");
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, HIGH);
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, HIGH);
        break;

      case leftOnCode:
      Serial.println("Gone left");
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, HIGH);
        digitalWrite(in1B, HIGH);
        digitalWrite(in2B, LOW);
        break;

      case rightOnCode:
      Serial.println("Gone right");
        digitalWrite(in1A, HIGH);
        digitalWrite(in2A, LOW);
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, HIGH);
        break;

      case SpeedControl1:
      Serial.println("1st gear");
        analogWrite(pwmA, speed0);
        analogWrite(pwmB, speed0);
        break;

      case SpeedControl2:
      Serial.println("2nd gear");
        analogWrite(pwmA, speed1);
        analogWrite(pwmB, speed1);
        break;

      case SpeedControl3:
      Serial.println("3rd gear");
        analogWrite(pwmA, speed2);
        analogWrite(pwmB, speed2);
        break;

      case SpeedControl4:
      Serial.println("4th gear");
        analogWrite(pwmA, speed3);
        analogWrite(pwmB, speed3);
        break;

      case SpeedControl5:
      Serial.println("5th gear");
        analogWrite(pwmA, speed4);
        analogWrite(pwmB, speed4);
        break;
    }

    delay(1);
    IrReceiver.resume();
  }
}
