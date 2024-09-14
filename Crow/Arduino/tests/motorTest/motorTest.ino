#include <Motors.h>
#include "encoder.h"
Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin
void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  Serial3.begin(9600);
  Serial2.begin(9600);

  pinMode(41, INPUT);
  pinMode(3, INPUT);

  attachInterrupt(digitalPinToInterrupt(3), enc, RISING);
}

void loop() {
  Serial.println(value);
  motorA.set(30);
}
