#include <Motors.h>
#include "encoder.h"
Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin

float kp = 0.7, kd = 1.5, u = 0, uLim = 0, kLim = 1, kS = 0.8;
int pos = 0, pos_old = 0, err_old = 0, vel = 20, err = 0, countFox = 0;

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
  if (Serial3.available() != 0) {   //запуск цикла отслеживания Лисы
    pos = Serial3.read() - 80;
    pos = int((pos + pos_old) / 2);
    pos_old = pos;
    
    if (pos != 0  && pos != -80) {    //регулятор отслеживания Лисы
      err = pos - (value / 4);
      u = err * kp + (err - err_old) * kd;
      err_old = err;
      if (u > 40)
        u = 40;
      if (u < -40)
        u = -40;

      Serial.print("pos = ");
      Serial.print(pos);
      Serial.print("  ");
      Serial.print("enc = ");
      Serial.print(value / 4);
      Serial.print("  ");//*/
        
      motorA.set(u * kS);
    }
  }
  else
    motorA.stop();
}
