#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include <Motors.h>
#include "handleGesture.h"
#include "eyes.h"
#include "wire.h"
#include "hand.h"
#include "motors.h"
#include "leds.h"
#include "wings.h"
#include "turnForFox.h"
#include "shotCheese.h"

#define pinPWMRotaionCrows 14
#define pinDIGRotaionCrows 41
#define pinInterruptCrows 3

#define pinServoEyeLeft 7
#define pinServoEyeRight 6
#define pinServoWingPlaneLeft 5
#define pinServoWingPlaneRight 13
#define pinServoWingTurnLeft 8
#define pinServoWingTurnRight 9
#define pinServoStrela 10
#define pinServoHand 9
#define pinServoOpening 10

DFRobotDFPlayerMini playerCrow;

uint32_t myTime = millis();
uint32_t timerEyes = millis();

int currentConditionCrows;
int fileTransferSpeed = 9600;

Servo myservo;

void setup() {                                                     // как start
  FastLED.addLeds<NEOPIXEL, pinLedEyeLeft>(ledLeft, countLeds);
  FastLED.addLeds<NEOPIXEL, pinLedEyeRight>(ledRight, countLeds);
  Serial.begin(fileTransferSpeed);
  Serial2.begin(fileTransferSpeed);  //камера
  Serial3.begin(fileTransferSpeed);  //плеер

  lidLeft.attach(pinServoEyeLeft);
  lidRight.attach(pinServoEyeRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  wingPlaneL.attach(pinServoWingPlaneLeft);
  wingPlaneR.attach(pinServoWingPlaneRight);
  
  strela.attach(pinServoStrela);

  hand.attach(pinServoHand);
  opening.attach(pinServoOpening);

  //ann_handleGesture();
  ann_wire();

  ann_motor(pinPWMRotaionCrows, pinDIGRotaionCrows);
  ann_enc(pinInterruptCrows);
}

void loop() {  // как update
  /*moveEyeLeft();
  moveEyeRight();
  switch (currentConditionCrows) {
    case 0:
      break;
    case 1:  //Ворона поворачивается в сторону Лисицы (движения Вороны изображающие радость),всё ещё держит сыр
      if (Serial3.available() != 0) {
        pos = Serial3.read() - 80;
        if ((pos < 0 && pos > -5) || (pos < 5 && pos > 0)) {
          pos = 0;
        }

        if (pos != 0)  {
          err = pos - (value / 4);
          u = err * kp + (err - err_old) * kd;
          err_old = err;

          (u > 30) ? u = 30 : u = u;
          (u < -30) ? u = -30 : u = u;

          motorA.set(u);

          ambientTemp = sensor.getAmbientTempCelsius();
          objectTemp = sensor.getObjectTempCelsius();
          if ((ambientTemp > 600 && objectTemp > -90) || (ambientTemp > 24 && objectTemp > 28)) {
            kar = true;
          }

          if (kar && (value / 4 > -5 && value / 4 < 5)) {
            motorA.stop();
            shotCheese(1000);
            currentConditionCrows++;
          }
          else if (value / 4 > -5 && value / 4 < 5) {
            wingTurnRight(0);
            wingTurnLeft(0);
          }
        }
        else {
          motorA.stop();
        }
      }
      break;
    case 3:  //Ворона сидит без сыра, грутсно опустив голову. При поглажеваниях ее головы, шевелит крыльями и веками глаз
      break;
    default: break;
  }*/
}
