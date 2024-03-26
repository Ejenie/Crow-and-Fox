#include <Motors.h>

Motors motorA = Motors(9, 23, 22, 5, 48); //pinPWM, pinA, pinB, interruptNumber, directionPin

bool direct = true;
float kp = 1.5, kd = 0, u = 0;
int i = 0, pos = 0, err_old = 0, vel = 40, err = 0;
uint32_t myTimer = millis();
int32_t value = 0;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(14, INPUT);
  pinMode(48, INPUT);
  attachInterrupt(5, enc, RISING);
  myTimer = millis();
}

void loop() {
  if (Serial3.available() != 0) {
    pos = Serial3.read() - 80;

    if ( (pos < 0 && pos > -5) || (pos > 0 && pos < 5))
      pos = 0;
      
    if (pos != 0) {
      err = pos - (value / 5);
      u = err * kp + (err - err_old) * kd;
      err_old = err;
      if (u > 50)
        u = 50;
      if (u < -50)
        u = -50;
      motorA.set(-u);
    }
    else
      motorA.stop();

    Serial.print(pos);
    Serial.print("  ");
    Serial.print(value/5);
    Serial.print("  ");
    Serial.println(u);
  }
}
