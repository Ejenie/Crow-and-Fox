//current on 07.09.24❤❤
#include <DFRobot_MLX90614.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include <Motors.h>

/*#include "eyes.h"
  #include "wire.h"
  #include "head.h"
  #include "motors.h"
  #include "leds.h"
  #include "wings.h"
  #include "turnForFox.h"
  #include "shotCheese.h"
  #include "APDS9960.h"
  #include "tail.h"
  #include "declaring.h"*/
#include "handleGesture.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  Serial3.begin(9600);
  Serial2.begin(9600);

  pinMode(DTX, INPUT);
  pinMode(CLKX, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);

  pinMode(PWM, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(A2, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLK), isrTail, RISING);  // прерывание на 2 пине! CLK у энка

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

  head.attach(pinServohead);
  opening.attach(pinServoOpening);
  
                      //начальные положения серво-моторов
  wingTurnLeft(10);    //от 10 до 160
  wingTurnRight(170);   //от 170 до 70

  wingPlaneLeft(10);
  wingPlaneRight(170);

  moveLidLeft(170);
  moveLidRight(10);

  lidRight.write(10);
  lidLeft.write(170);

  head.write(0);

  motor(130);
  delay(130);
  while (TailCurrentLimit <= 100) {
    TailCurrentLimit = analogRead(A2);
    Serial.print("tail  ");
    Serial.println(TailCurrentLimit);
  }
  encTail = 0;
  motor(0);

  permanentLeds(pinLedEyeLeft, 0xDDAA00);
  permanentLeds(pinLedEyeRight, 0xDDAA00);
}

void loop() {
  if (flagBegin && (millis() - timerWait < 18000)) {    //вступительные слова рассказчика
    for (int i = 0; i < 3; i++) {
      opening.write(0);
      delay(400);
      opening.write(50);
      delay(400);
    }
    delay(3600);
  }
  if (Serial3.available() != 0 && (millis() - timerWait > 23000)) {   //запуск цикла отслеживания Лисы
    flagBegin  = false;
    pos = Serial3.read() - 80;
    pos = int((pos + pos_old) / 2);
    pos_old = pos;

    if ((pos < 0 && pos > -5) || (pos > 0 && pos < 5)) {    //позиция Лисы - центр
      pos = 0;
      if (millis() - timerFox > 3000) {
        timerFox = millis();
        countFox++;
        Serial.print("Кол-во появлений лисы:  ");
        Serial.println(countFox);//
        switch (countFox) {   //действия Вороны на слова Лисы
          case 3:
            motorA.stop();
            for (int i = 0; i < 2; i++) {
              head.write(100);
              delay(700);
              head.write(0);
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
            for (int i = 0; i < 3; i++) {
              wingTurnLeft(20);
              wingTurnRight(160);
              delay(600);
              wingTurnRight(110);
              wingTurnLeft(110);
              delay(600);
            }
            break;
          default: break;
        }
        permanentLeds(pinLedEyeLeft, 0xDDAA00);
        permanentLeds(pinLedEyeRight, 0xDDAA00);
      }
    }

    wingTurnLeft(10);
    wingTurnRight(170);

    if (pos != 0  && pos != -80) {    //регулятор отслеживания Лисы
      err = pos - (value / 4);
      u = err * kp + (err - err_old) * kd;
      err_old = err;
      if (u > 30)
        u = 30;
      if (u < -30)
        u = -30;

      Serial.print("pos = ");
      Serial.print(pos);
      Serial.print("  ");
      Serial.print("enc = ");
      Serial.println(value / 4);//*/
      /*Serial.print("u = ");
        Serial.print(u);*/

      motorA.set(u * kS);

      if (kar && (value / 4) > -5 && (value / 4) < 5) {   //готовность к выстреливанию сыром
        Serial.println("kar");
        motorA.stop();
        playerCrow.play(1);   //КАР!
        strela.write(500);    //выстрел сыром
        delay(1000);
        strela.write(90);

        permanentLeds(pinLedEyeLeft, 0xFFFFFF);
        permanentLeds(pinLedEyeRight, 0xFFFFFF);

        for (int i = 0; i < 3; i++) {
          lidRight.write(140);
          lidLeft.write(20);
          delay(1000);
          lidRight.write(10);
          lidLeft.write(170);
          delay(1000);
        }
        wingPlaneRight(170);
        wingPlaneLeft(10);

        wingTurnRight(110);
        wingTurnLeft(90);

        head.write(0);
        for (int i = 0; i < 4; i++) {
          opening.write(0);
          delay(400);
          opening.write(50);
          delay(400);
        }
        opening.write(0);
        delay(400);

        permanentLeds(pinLedEyeLeft, 0x2222FF);
        permanentLeds(pinLedEyeRight, 0x2222FF);

        lidRight.write(80);
        lidLeft.write(130);

        tailClosed();
        wingTurnLeft(10);
        wingTurnRight(170);
        delay(15000);
        kar = false;
        kS = 0;
      }

      float ambientTemp = sensor.getAmbientTempCelsius();
      float objectTemp = sensor.getObjectTempCelsius();

      if ((ambientTemp > 600 && objectTemp >= -50)  || (ambientTemp > 20 && (objectTemp - ambientTemp) >= 10) && flagTemp) {   //обнаружение руки датчиком температуры
        motorA.stop();
        Serial.println("temp");
        flagTemp = false;
        tailOpen();   //открытие хвоста
        head.write(100);

        permanentLeds(pinLedEyeLeft, 0xFF9900);
        permanentLeds(pinLedEyeRight, 0xFF9900);
        kar = true;
      }
      else
        handleGesture();  //выстрел по датчику жестов

      if (isr_flag == 1) {
        detachInterrupt(5);
        handleGesture();
        isr_flag = 0;
        attachInterrupt(5, interruptRoutine, FALLING);
      }
    }
    else
      motorA.stop();    //остановка в случае нахождения Лисы по центру
  }
}
