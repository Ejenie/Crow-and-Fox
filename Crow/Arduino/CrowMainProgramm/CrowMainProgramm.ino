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
#define pinInterruptTail 3

#define pinServoEyeLeft 33
#define pinServoEyeRight 13
#define pinServoWingPlaneLeft 5
#define pinServoWingPlaneRight 13
#define pinServoWingTurnLeft 12
#define pinServoWingTurnRight 14
#define pinServoStrela 48
#define pinServoHand 9
#define pinServoOpening 10

#define APDS9960_INT 2

DFRobotDFPlayerMini playerCrow;

uint32_t myTime = millis();
uint32_t timerEyes = millis();
uint32_t timerTemp = millis();
uint32_t timerCamera = millis();

int currentConditionCrows = 0, countTemp = 0;
int fileTransferSpeed = 9600;

void setup() {                                                     // как start
  FastLED.addLeds<NEOPIXEL, pinLedEyeLeft>(ledLeft, countLeds);
  FastLED.addLeds<NEOPIXEL, pinLedEyeRight>(ledRight, countLeds);
  Serial.begin(fileTransferSpeed);
  Serial3.begin(fileTransferSpeed);  //камера
  Serial2.begin(fileTransferSpeed);  //плеер

  playerCrow.begin(Serial2);  //инициализируем плеер
  playerCrow.volume(30);      //от 10 до 30

  lidLeft.attach(pinServoEyeLeft);
  lidRight.attach(pinServoEyeRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  wingPlaneL.attach(pinServoWingPlaneLeft);
  wingPlaneR.attach(pinServoWingPlaneRight);

  strela.attach(pinServoStrela);

  hand.attach(pinServoHand);
  opening.attach(pinServoOpening);

  ann_wire();

  ann_motor(pinPWMRotaionCrows, pinDIGRotaionCrows);
  attachInterrupt(digitalPinToInterrupt(pinInterruptCrows), enc, RISING);
  attachInterrupt(digitalPinToInterrupt(pinInterruptTail), encTail, RISING);
}

void loop() {  // как update
  currentConditionCrows = 0;
  switch (currentConditionCrows) {
    case 0:
      while (currentConditionCrows == 0) {
        if (Serial3.available() != 0) {
          timerCamera = millis();
          permanentLeds(pinLedEyeLeft, 0x00FF00);
          permanentLeds(pinLedEyeRight, 0x00FF00);
          pos = Serial3.read() - 80;
          if ((pos < 0 && pos > -5) || (pos < 5 && pos > 0)) {
            pos = 0;
          }
          Serial.println(currentConditionCrows);
          if (pos != 0)  {
            err = pos - (value / 4);
            u = err * kp + (err - err_old) * kd;
            err_old = err;

            (u > 40) ? u = 40 : u = u;
            (u < -40) ? u = -40 : u = u;
            motorA.set(u);
            float ambientTemp = sensor.getAmbientTempCelsius();
            float objectTemp = sensor.getObjectTempCelsius();
            if ((ambientTemp > 600 && objectTemp > -90) || (ambientTemp > 24 && objectTemp > 28)) {
              Serial.println("Temperature detected");
              permanentLeds(pinLedEyeLeft, 0x000000);
              permanentLeds(pinLedEyeRight, 0x000000);
              kar = true;
            }
            if (kar && (value / 4 > -5 && value / 4 < 5)) {
              motorA.stop();
              shotCheese(1000);
              playerCrow.play(1);
              delay(5000);
              changeLeds(pinLedEyeLeft, 0x000000, 6, 200);
              changeLeds(pinLedEyeRight, 0x000000, 6, 200);
              currentConditionCrows++;
            }
            if (value / 4 > -5 && value / 4 < 5 && ((millis() - timerTemp) > 1000)) {
              timerTemp = millis();
              countTemp++;
              wingTurnRight(70);
              wingTurnLeft(70);
            }

          }
          else {
            Serial.println(currentConditionCrows);
            motorA.stop();
          }
        }
      }
      Serial.println("Gg");
      break;
    case 1:  //Ворона сидит без сыра, грутсно опустив голову. При поглажеваниях ее головы, шевелит крыльями и веками глаз
      Serial.println("case 1");
      changeLeds(pinLedEyeLeft, 0x0000FF, 6, 200);
      changeLeds(pinLedEyeRight, 0x0000FF, 6, 200);
      break;
    default: break;
  }
}
