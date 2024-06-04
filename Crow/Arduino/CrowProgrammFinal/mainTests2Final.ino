#include <Motors.h>
#include <DFRobot_MLX90614.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

#include "handleGesture.h"
#include "eyes.h"
#include "wire.h"
#include "hand.h"
#include "motors.h"
#include "leds.h"
#include "wings.h"
#include "turnForFox.h"
#include "shotCheese.h"
#include "APDS9960.h"
#include "tail.h"

#define pinServoEyeLeft 13
#define pinServoEyeRight 35
#define pinServoWingPlaneLeft 9
#define pinServoWingPlaneRight 46
#define pinServoWingTurnLeft 5
#define pinServoWingTurnRight 6
#define pinServoStrela 48
#define pinServoHand 8
#define pinServoOpening 7

Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(10, 39, 31, 2, 40);  //pinPWM, pinA, pinB, interruptNumber, directionPin

DFRobotDFPlayerMini playerCrow;

bool kar = false, flag = true;
float kp = 0.7, kd = 1.5, u = 0, i = 0, ki = 0.001;
int pos = 0, err_old = 0, vel = 20, err = 0, countFox = 0;

uint32_t timerWait = millis(), timerFox = millis();

void handleGesture() {    //функция состояний датчика жестов
  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:
        motorA.stop();
        tailOpen();
        hand.write(100);
        permanentLeds(pinLedEyeLeft, 0xFF7700);
        permanentLeds(pinLedEyeRight, 0xFF7700);
        kar = true;
        break;

      case DIR_DOWN:
        motorA.stop();
        permanentLeds(pinLedEyeLeft, 0xFF2277);
        permanentLeds(pinLedEyeRight, 0xFF2277);

        for (int i = 0; i < 3; i++) {
          lidRight.write(140);
          lidLeft.write(30);
          delay(500);
          lidRight.write(10);
          lidLeft.write(170);
          delay(500);
        }
        for (int i = 0; i < 3; i++) {
          wingTurnLeft(40);
          wingTurnRight(90);
          delay(500);
          wingTurnLeft(90);
          wingTurnRight(40);
          delay(500);
        }

        tailOpen();

        wingTurnLeft(90);
        wingTurnRight(90);

        delay(2000);
        tailClosed();
        break;
      default:
        Serial.println("NONE");
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  Serial3.begin(9600);
  Serial2.begin(9600);

  pinMode(41, INPUT);
  pinMode(3, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);

  pinMode(PWM, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(A2, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLK), isrTail, RISING);  // прерывание на 2 пине! CLK у энка

  pinMode(DTX, INPUT);
  pinMode(CLKX, INPUT);

  // Инициализируем APDS-9960
  if (apds.init()) {
    Serial.println(F("APDS-9960 initialization complete"));
  }
  else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  if (apds.enableGestureSensor(true)) {
    Serial.println(F("Gesture sensor is now running"));
  }
  else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  playerCrow.begin(Serial2);  //инициализируем плеер
  playerCrow.volume(30);      //от 10 до 30

  attachInterrupt(digitalPinToInterrupt(3), enc, RISING);

  FastLED.addLeds<NEOPIXEL, pinLedEyeLeft>(ledLeft, countLeds);
  FastLED.addLeds<NEOPIXEL, pinLedEyeRight>(ledRight, countLeds);

  while (NO_ERR != sensor.begin()) {    //выявление ошибок в подключении датчика тепла
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
  sensor.setEmissivityCorrectionCoefficient(1.0);
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);


  sensor.enterSleepMode();    //импульс датчика тепла
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);

  lidLeft.attach(pinServoEyeLeft);    //объявление серво-моторов
  lidRight.attach(pinServoEyeRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  wingPlaneL.attach(pinServoWingPlaneLeft);
  wingPlaneR.attach(pinServoWingPlaneRight);

  strela.attach(pinServoStrela);

  hand.attach(pinServoHand);
  opening.attach(pinServoOpening);

  wingTurnLeft(180);    //начальные положения серво-моторов
  wingTurnRight(180);

  wingPlaneLeft(0);
  wingPlaneRight(180);

  lidRight.write(10);
  lidLeft.write(170);

  hand.write(0);

  permanentLeds(pinLedEyeLeft, 0x00FF00);
  permanentLeds(pinLedEyeRight, 0x00FF00);
  motor(130);
  delay(130);
  while (TailCurrentLimit <= 100) {
    TailCurrentLimit = analogRead(A2);
    Serial.println("tail");
    Serial.println(TailCurrentLimit);
  }
  permanentLeds(pinLedEyeLeft, 0xDDAA00);
  permanentLeds(pinLedEyeRight, 0xDDAA00);
  encTail = 0;
  motor(0);
  delay(1000);
}
void loop() {
  if (Serial3.available() != 0 && (millis() - timerWait > 17000)) {
    pos = Serial3.read() - 80;

    if ((pos < 0 && pos > -5) || (pos > 0 && pos < 5)) {
      pos = 0;
      if (millis() - timerFox > 2500) {
        timerFox = millis();
        countFox++;
        switch (countFox) {
          case 3:
            motorA.stop();
            permanentLeds(pinLedEyeLeft, 0xFF9900);
            permanentLeds(pinLedEyeRight, 0xFF9900);
            for (int i = 0; i < 2; i++) {
              hand.write(100);
              delay(700);
              hand.write(0);
              delay(700);
            }
            lidRight.write(140);
            lidLeft.write(30);
            delay(500);
            lidRight.write(10);
            lidLeft.write(170);
            permanentLeds(pinLedEyeLeft, 0xDDAA00);
            permanentLeds(pinLedEyeRight, 0xDDAA00);
            delay(500);
            break;
          case 5:
            motorA.stop();
            for (int i = 0; i < 4; i++) {
              wingTurnLeft(30);
              wingTurnRight(100);
              delay(500);
              wingTurnLeft(100);
              wingTurnRight(30);
              delay(500);
            }
            break;
          default: break;
        }
      }
    }

    if (pos != 0) {
      err = pos - (value / 4);
      i += err * ki;
      u = err * kp + (err - err_old) * kd;
      err_old = err;
      if (u > 40)
        u = 40;
      if (u < -40)
        u = -40;
      Serial.println(value / 4);
      
      motorA.set(u - (60 - abs(value / 4)));

      if (kar && value / 4 > -5 && value / 4 < 5) {
        motorA.stop();
        playerCrow.play(1);
        strela.write(500);
        delay(1000);
        strela.write(90);

        permanentLeds(pinLedEyeLeft, 0xFFFFFF);
        permanentLeds(pinLedEyeRight, 0xFFFFFF);

        for (int i = 0; i < 3; i++) {
          lidRight.write(140);
          lidLeft.write(30);
          delay(500);
          lidRight.write(10);
          lidLeft.write(170);
          delay(500);
        }

        wingTurnLeft(170);
        wingTurnRight(150);

        wingPlaneRight(180);
        wingPlaneLeft(0);

        hand.write(0);
        for (int i = 0; i < 4; i++) {
          opening.write(0);
          delay(400);
          opening.write(50);
          delay(400);
        }
        opening.write(0);
        delay(400);

        permanentLeds(pinLedEyeLeft, 0x0000FF);
        permanentLeds(pinLedEyeRight, 0x0000FF);

        lidRight.write(50);
        lidLeft.write(130);

        tailClosed();
        delay(15000);
        kar = false;
      }

      float ambientTemp = sensor.getAmbientTempCelsius();
      float objectTemp = sensor.getObjectTempCelsius();

      //Serial.print(objectTemp);
      //Serial.print(' ');
      //Serial.println(ambientTemp);
      if ((ambientTemp > 600 && objectTemp >= -60) || (ambientTemp > 20 && (objectTemp - ambientTemp) >= 4)) {
        motorA.stop();
        tailOpen();
        wingPlaneLeft(90);
        wingPlaneRight(90);
        hand.write(100);
        permanentLeds(pinLedEyeLeft, 0xFF7700);
        permanentLeds(pinLedEyeRight, 0xFF7700);
        kar = true;
      }
      else
        handleGesture();
      if (isr_flag == 1) {
        detachInterrupt(5);
        handleGesture();
        isr_flag = 0;
        attachInterrupt(5, interruptRoutine, FALLING);
      }
    }
    else
      motorA.stop();
  }
}
