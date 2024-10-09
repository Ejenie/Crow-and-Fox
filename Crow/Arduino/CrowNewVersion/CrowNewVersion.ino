#include "motors.h"
#include "APDS9960.h"
#include "MLX90614.h"
#include <stdio.h>
#define timeCode 20

Rotation rot;
Myservo servo;
Tail tail;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial2.begin(9600);
  Serial.flush();
  Serial3.flush();
  led.init_leds();
  init_apds();
  init_player();
  rot.init_motor_rotation();
  rot.init_enc_rotation();
  init_temp();
  tail.init_enc_tail();
  tail.init_motor_tail();
  servo.init_servo();

  servo.basic_servo();
  led.permanentLeds(pinLedEyeLeft, 0xDDAA00);
  led.permanentLeds(pinLedEyeRight, 0xDDAA00);
  tail.calibrovka();
  servo.Begin();//*/
}

void loop() {
  static uint32_t timerCode = millis();
  while (millis() - timerCode < timeCode);
  timerCode = millis();

  PosCount fox = camera();
  static int co = fox.count;
  int pos = fox.pos, countFox = fox.count - co;
  float objTemp = objectTemp(), ambTemp = ambientTemp();
  int handle = handleGesture();

  bool kar = ((ambTemp > 600.0 && objTemp >= -7.0)  || (ambTemp > 18.0 && (objTemp - ambTemp) >= 10.0));
  static bool kar0 = false;
  static bool fK = true;
  static bool flagKar0  = false;
  if (kar)
    kar0 = true;
  if (fK)
    flagKar0 = (kar0 && (value / 4) > -10 && (value / 4) < 0);
  ServoPos sP = servo.positionServo(countFox, kar0, flagKar0, 0);
  int wTr = sP.wTr, wTl = sP.wTl, wPr = sP.wPr,
      wPl = sP.wPl, mLr = sP.mLr, mLl = sP.mLl,
      mH = sP.mH, mO = sP.mO, mS = sP.mS;

  float u = rot.need_for_a_motor(flagKar0, handle, pos);
  if ((flagKar0 || handle == 1) && fK) {
    rot.motor_rot_stop();
    fK = false;
    flagKar0 = true;
    playerCrow.play(1);   //КАР!
    strela.write(500);    //выстрел сыром
    delay(1000);
    strela.write(90);
    led.permanentLeds(pinLedEyeLeft, 0xFFFFFF);
    led.permanentLeds(pinLedEyeRight, 0xFFFFFF);

    for (int i = 0; i < 3; i++) {
      servo.moveLidRight(140);
      servo.moveLidLeft(20);
      delay(600);
      servo.moveLidRight(10);
      servo.moveLidLeft(170);
      delay(600);
    }

    servo.moveHead(0);
    for (int i = 0; i < 3; i++) {
      servo.moveOpening(20);
      delay(400);
      servo.moveOpening(50);
      delay(400);
    }
    servo.wingTurnRight(90);
    servo.wingTurnLeft(150);
    for (int i = 0; i < 3; i++) {
      servo.wingPlaneRight(90);
      servo.wingPlaneLeft(90);
      delay(600);
      servo.wingPlaneRight(170);
      servo.wingPlaneLeft(10);
      delay(600);
    }
    servo.wingTurnLeft(10);
    servo.wingTurnRight(170);
    led.permanentLeds(pinLedEyeLeft, 0x2222FF);
    led.permanentLeds(pinLedEyeRight, 0x2222FF);
    tail.tailClosed(true);

    servo.moveLidRight(50);
    servo.moveLidLeft(105);
    servo.moveHead(0);
  }
  if (handle == 2) {
    rot.motor_rot_stop();
    led.permanentLeds(pinLedEyeLeft, 0xFF2277);
    led.permanentLeds(pinLedEyeRight, 0xFF2277);

    for (int i = 0; i < 3; i++) {
      servo.moveLidRight(140);
      servo.moveLidLeft(20);
      delay(500);
      servo.moveLidRight(10);
      servo.moveLidLeft(170);
      delay(500);
    }
    tail.tailOpen(true, 0);
    for (int i = 0; i < 3; i++) {
      servo.wingTurnLeft(20);
      servo.wingTurnRight(160);
      delay(700);
      servo.wingTurnRight(110);
      servo.wingTurnLeft(110);
      delay(700);
    }
    servo.wingTurnLeft(90);
    servo.wingTurnRight(110);
  }

  if (kar0) tail.tailOpen(kar0, 0);
  rot.motor_rot_set (u);
  servo.wingTurnRight(wTr);
  servo.wingTurnLeft(wTl);
  servo.wingPlaneRight(wPr);
  servo.wingPlaneLeft(wPl);
  servo.moveLidRight(mLr);
  servo.moveLidLeft(mLl);
  servo.moveHead(mH);
  servo.moveOpening(mO);
  servo.moveStrela(mS);
}//*/
