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

DFRobotDFPlayerMini player_crow;

const int pinLEDEye = 45;
const int pinPWMRotaionCrows = 14;
const int pinDIGRotaionCrows = 48;

int currentConditionCrows;
int fileTransferSpeed = 9600;

void setup() {                                          // как start
  FastLED.addLeds<NEOPIXEL, pinLEDEye>(eyesLeds, countLeds);  // GRB ordering is assumed
  Serial.begin(fileTransferSpeed);
  Serial2.begin(fileTransferSpeed);  //камера
  Serial3.begin(fileTransferSpeed);  //плеер

  lidLeft.attach(8);
  lidRight.attach(9);

  //ann_handleGesture();
  ann_wire();

  ann_motor(pinPWMRotaionCrows, pinDIGRotaionCrows);
  ann_enc(pinDIGRotaionCrows);
}

void loop() {  // как update
  
  FastLED.show();
  switch (currentConditionCrows) {
    case 0:  //сидит на дереве, держит сыр
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
