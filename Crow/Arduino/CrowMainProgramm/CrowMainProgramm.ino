#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include <Motors.h>
#include "handleGesture.h"
#include "eyes.h"
#include "wings.h"
#include "wire.h"
#include "other_servo.h"
#include "motors.h"
#include "leds.h"
#include "turnWings.h"

DFRobotDFPlayerMini playerCrow;

uint32_t myTime = millis();
uint32_t timerEyes = millis();
const int pinPWMRotaionCrows = 14;
const int pinDIGRotaionCrows = 48;
const int pinServoEyeLeft = 7;
const int pinServoEyeRight = 6;
const int pinServoWingLeft = 5;
const int pinServoWingRight = 13;
const int pinServoWingTurnLeft = 8;
const int pinServoWingTurnRight = 9;

int currentConditionCrows;
int fileTransferSpeed = 9600;

void setup() {                                                     // как start
  FastLED.addLeds<NEOPIXEL, pinLedEyeLeft>(ledLeft, countLeds);
  FastLED.addLeds<NEOPIXEL, pinLedEyeRight>(ledRight, countLeds);
  Serial.begin(fileTransferSpeed);
  Serial2.begin(fileTransferSpeed);  //камера
  Serial3.begin(fileTransferSpeed);  //плеер

  lidLeft.attach(pinServoEyeLeft);
  lidRight.attach(pinServoEyeRight);

  wingL.attach(pinServoWingLeft);
  wingR.attach(pinServoWingRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  //ann_handleGesture();
  ann_wire();

  ann_motor(pinPWMRotaionCrows, pinDIGRotaionCrows);
  ann_enc(pinDIGRotaionCrows);
}

void loop() {  // как update
  moveEyeLeft();
  moveEyeRight();
  permanentLeds(24, 0xFFFFFF);
  permanentLeds(25, 0xFFFFFF);
  switch (currentConditionCrows) {
    case 0:
      break;
    case 1:  //Ворона поворачивается в сторону Лисицы (движения Вороны изображающие радость),всё ещё держит сыр
      break;
    case 2:  //Ворона открывает клюв, сыр выбрасывается к Лисице
      break;
    case 3:  //Ворона сидит без сыра, грутсно опустив голову. При поглажеваниях ее головы, шевелит крыльями и веками глаз
      break;
    default: break;
  }
}
