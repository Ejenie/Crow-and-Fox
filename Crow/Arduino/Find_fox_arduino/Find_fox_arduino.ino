#include <Motors.h>
#include "encoder.h"
#include "interesting_functions.h"
Motors motorA = Motors(11, 49, 43, 3, 41); //pinPWM, pinA, pinB, interruptNumber, directionPin

bool direct = true;
float kp = 1.5, kd = 5, ki = 0.001, u = 0, i = 0;
int pos = 0, err_old = 0, vel = 40, err = 0;
uint32_t myTimer = millis();

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  Serial3.begin(9600);
  pinMode(41, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), enc, RISING);
  myTimer = millis();
}

void loop() {
  if (Serial3.available() != 0) {
    pos = Serial3.read() - 80;

    if (-1 < pos && pos < 1)
      pos = 0;

    if (pos != 0) {
      err = pos - (value / 5);
      i += err * ki;
      if (abs(i) > 5)
        i = 5 * sign(i);
      u = err * kp + (err - err_old) * kd;//+i
      err_old = err;
      if (u > 50)
        u = 50;
      if (u < -50)
        u = -50;
      motorA.set(-u);
    } else {
      motorA.stop();
    }
    Serial.print("Камера: ");
    Serial.print(pos);
    Serial.print("   Энкодер: ");
    Serial.print(value / 5);
    Serial.print("  Упр. возд.: ");
    Serial.println(u);
  }  
  motorA.stop();
}
