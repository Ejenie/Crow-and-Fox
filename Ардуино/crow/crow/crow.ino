#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include <Motors.h>
#include "handleGesture.h"
#include "eyes.h"
#include "wings.h"
#include "wire.h"
#include "other_servo.h"
#include "motors.h"

DFRobotDFPlayerMini player_crow;

int currentConditionCrows;
int pinPWMRotaionCrows = 14;
int pinDIGRotaionCrows = 48;
int fileTransferSpeed = 9600;

void setup() {                         // как start
  Serial.begin(fileTransferSpeed);
  Serial2.begin(fileTransferSpeed);    //камера
  Serial3.begin(fileTransferSpeed);    //плеер

  ann_handleGesture();
  ann_wire();

  ann_motor(pinPWMRotaionCrows, pinDIGRotaionCrows);
  ann_enc(pinDIGRotaionCrows);
}

void loop() {                         // как update
  switch (currentConditionCrows) {
    case 0:   //сидит на дереве, держит сыр
      break;
    case 1:   //Ворона поворачивается в сторону Лисицы (движения Вороны изображающие радость),всё ещё держит сыр
      break;
    case 2:   //Ворона открывает клюв, сыр выбрасывается к Лисице
      break;
    case 3:   //Ворона сидит без сыра, грутсно опустив голову. При поглажеваниях ее головы, шевелит крыльями и веками глаз
      break;
    default: break;
  }
}
