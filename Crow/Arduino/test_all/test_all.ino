//current on 13.09❤❤
#include <DFRobot_MLX90614.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
//#include <ServoSmooth.h>
#include <Motors.h>

#include "eyes.h"
#include "MLX90614.h"
#include "head.h"
#include "motors.h"
#include "leds.h"
#include "wings.h"
#include "shotCheese.h"
#include "APDS9960.h"
#include "tail.h"

#define pinServoEyeLeft 13
#define pinServoEyeRight 35
#define pinServoWingPlaneLeft 9
#define pinServoWingPlaneRight 46
#define pinServoWingTurnRight 6
#define pinServoWingTurnLeft 5
#define pinServoStrela 48
#define pinServoHand 8
#define pinServoOpening 7

Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin

DFRobotDFPlayerMini playerCrow;

bool flagBegin = true, kar = false, flagTemp = true;
float kp = 1, kd = 1.6, u = 0, uLim = 0, kLim = 1, kS = 0.96;
int pos = 0, pos_old = 0, err = 0, err_old = 0, countFox = 0;

uint32_t timerWait = millis(), timerFox = millis();

void handleGesture() {    //функция состояний датчика жестов
  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:    //движение рукой вверх: запасной вариант при отказе датчика тепла
        Serial.println("zhest");
        motorA.stop();
        tailOpen();
        head.write(100);
        permanentLeds(pinLedEyeLeft, 0xFF7700);
        permanentLeds(pinLedEyeRight, 0xFF7700);
        kar = true;
        break;

      case DIR_DOWN:    //движение рукой вниз: финальные действия Вороны
        motorA.stop();
        Serial.println("down");
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
          wingTurnLeft(20);
          wingTurnRight(160);
          delay(700);
          wingTurnRight(110);
          wingTurnLeft(110);
          delay(700);
        }
        wingTurnLeft(90);
        wingTurnRight(110);
        tailOpen();
        delay(2000);
        for (int i = 0; i < 5; i++) {
          motorA.set(25);
          delay(3000);
          motorA.set(-25);
          delay(3000);
        }
        motorA.stop();
        tailClosed();
        break;
      case DIR_LEFT:    //движение рукой вверх: запасной вариант при отказе датчика тепла
        permanentLeds(pinLedEyeLeft, 0x337FA2);
        permanentLeds(pinLedEyeRight, 0x337FA2);
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

  if (apds.init()) {    // инициализация APDS-9960
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

  FastLED.addLeds<NEOPIXEL, pinLedEyeLeft>(ledLeft, countLeds);   //объявление светодиодных матриц
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

  lidLeft.attach(pinServoEyeLeft);    //инициализация серво-моторов
  lidRight.attach(pinServoEyeRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  wingPlaneL.attach(pinServoWingPlaneLeft);
  wingPlaneR.attach(pinServoWingPlaneRight);

  strela.attach(pinServoStrela);

  head.attach(pinServoHand);
  opening.attach(pinServoOpening);

  wingTurnLeft(10);    //от 10 до 160
  wingTurnRight(170);   //от 170 до 70

  wingPlaneLeft(10);
  wingPlaneRight(170);

  moveLidLeft(170);
  moveLidRight(10);

  lidRight.write(10);
  lidLeft.write(170);

  head.write(0);
  opening.write(20);

   /*motor(130);
    delay(130);
    while (TailCurrentLimit <= 100) {
     TailCurrentLimit = analogRead(A2);
     Serial.println("tail");
     Serial.println(TailCurrentLimit);
    }
    encTail = 0;
    motor(0);
  delay(5000);*/
}

void loop() {
  motor(130);
  delay(10000);
//  permanentLeds(pinLedEyeLeft, 0xDDAA00);
//  permanentLeds(pinLedEyeRight, 0xDDAA00);
//  delay(10000);
//  for (int i = 0; i < 2; i++) {
//    head.write(100);
//    delay(700);
//    head.write(0);
//    delay(700);
//  }
//  for (int i = 0; i < 5; i++) {
//    opening.write(0);
//    delay(400);
//    opening.write(50);
//    delay(400);
//  }
//  for (int i = 0; i < 5; i++) {
//    lidRight.write(140);
//    lidLeft.write(20);
//    delay(600);
//    lidRight.write(10);
//    lidLeft.write(170);
//    delay(600);
//  }
//  for (int i = 0; i < 5; i++) {
//    wingTurnLeft(20);
//    wingTurnRight(160);
//    delay(600);
//    wingTurnRight(110);
//    wingTurnLeft(110);
//    delay(600);
//  }
//  for (int i = 0; i < 5; i++) {
//    wingPlaneRight(90);
//    wingPlaneLeft(90);
//    delay(600);
//    wingPlaneRight(170);
//    wingPlaneLeft(10);
//    delay(600);
//  }
//  //tailOpen(); 
//  delay(3000);
//  wingTurnLeft(10);    //от 10 до 160
//  wingTurnRight(170);   //от 170 до 70
//
//  wingPlaneLeft(10);
//  wingPlaneRight(170);
//
//  moveLidLeft(170);
//  moveLidRight(10);
//
//  lidRight.write(10);
//  lidLeft.write(170);
//  
//  permanentLeds(pinLedEyeLeft, 0xFF2277);
//  permanentLeds(pinLedEyeRight, 0xFF2277);
//
//  delay(2000);
//  head.write(0);
//  opening.write(20);
//  playerCrow.play(1);   //КАР! 
//  strela.write(500);    //выстрел сыром
//  delay(1000);
//  strela.write(90);
//  delay(20000);
}
