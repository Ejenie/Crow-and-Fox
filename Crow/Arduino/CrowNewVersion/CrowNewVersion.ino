//#include "APDS9960.h"
#include "MLX90614.h"
#include "leds.h"
#include "servo.h"
#include "motors.h"
#define timeCode 20

Leds led;
Rotation rot;
Myservo servo;
Tail tail;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  led.init_leds();
  init_player();
  rot.init_motor_rotation();
  rot.init_enc_rotation();
  init_temp();
  tail.init_enc_tail();
  tail.init_motor_tail();
  servo.init_servo();

  servo.basic_servo();
}

void loop() {
  static uint32_t timerCode = millis();
  while (millis() - timerCode < timeCode);
  timerCode = millis();

  PosCount fox = camera();
  int pos = fox.pos, countFox = fox.count;
  Serial.println(pos);
  float objTemp = objectTemp(), ambTemp = ambientTemp();

  bool kar = ((ambTemp > 600.0 && objTemp >= -7.0)  || (ambTemp > 18.0 && (objTemp - ambTemp) >= 10.0));
  bool flagKar = (kar && (value / 4) > -5 && (value / 4) < 5);
  ServoPos sP = servo.positionServo(countFox, kar, flagKar);
  int wTr = sP.wTr, wTl = sP.wTl, wPr = sP.wPr,
      wPl = sP.wPl, mLr = sP.mLr, mLl = sP.mLl,
      mH = sP.mH, mO = sP.mO;
  float u = rot.need_for_a_motor(flagKar, pos); //rot.turn_fox(pos);

  rot.motor_rot_set(u);
  servo.wingTurnRight(wTr);
  servo.wingTurnLeft(wTl);
  servo.wingPlaneRight(wPr);
  servo.wingPlaneLeft(wPl);
  servo.moveLidRight(mLr);
  servo.moveLidLeft(mLl);
  servo.moveHead(mH);
  servo.moveOpening(mO);
}
