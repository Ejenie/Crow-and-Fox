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

int condition;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);    //камера
  Serial3.begin(9600);    //плеер

  ann_handleGesture();
  ann_wire();

  ann_motor(14, 48);
  ann_enc(48);
}

void loop() {
  switch (condition) {
    case 0:   //сидит на дереве, держит сыр
    case 1:   //Ворона поворачивается в сторону Лисицы (движения Вороны изображающие радость),всё ещё держит сыр

      break;
    case 2:   //Ворона открывает клюв, сыр выбрасывается к Лисице
      break;
    case 3:   //Ворона сидит без сыра, грутсно опустив голову. При поглажеваниях ее головы, шевелит крыльями и веками глаз
      break;
    default: break;
  }
}
