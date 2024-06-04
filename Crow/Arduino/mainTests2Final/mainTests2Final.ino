#include <Motors.h>
#include <DFRobot_MLX90614.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

#include "eyes.h"
#include "wire.h"
#include "hand.h"
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
#define pinServoWingTurnLeft 5
#define pinServoWingTurnRight 6
#define pinServoStrela 48
#define pinServoHand 8
#define pinServoOpening 7

DFRobotDFPlayerMini playerCrow;

bool kar = false, flag = true;
float kp = 0.7, kd = 1.5, u = 0, i = 0, ki = 0.001;
int pos = 0, err_old = 0, vel = 20, err = 0, countFox = 0;


void handleGesture() {
  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:
        tailOpen();
        hand.write(100);
        permanentLeds(pinLedEyeLeft, 0xFF7700);
        permanentLeds(pinLedEyeRight, 0xFF7700);
        kar = true;
        break;
      case DIR_DOWN:
        permanentLeds(pinLedEyeLeft, 0xDDAA00);
        permanentLeds(pinLedEyeRight, 0xDDAA00);

        wingTurnL.write(40);
        wingTurnR.write(67);

        lidRight.write(10);
        lidLeft.write(170);

        tailOpen();
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

  if (apds.init()) {  // Инициализируем APDS-9960
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

  while (NO_ERR != sensor.begin()) {  //инициализация датчика тепла
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
  sensor.setEmissivityCorrectionCoefficient(1.0);
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);


  sensor.enterSleepMode();
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);

  lidLeft.attach(pinServoEyeLeft);
  lidRight.attach(pinServoEyeRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  wingTurnL.write(40);
  wingTurnR.write(67);

  strela.attach(pinServoStrela);

  hand.attach(pinServoHand);
  opening.attach(pinServoOpening);


  lidRight.write(10);
  lidLeft.write(170);
  hand.write(0);
  permanentLeds(pinLedEyeLeft, 0xDDAA00);
  permanentLeds(pinLedEyeRight, 0xDDAA00);

  motor(130);
  delay(130);
  while (TailCurrentLimit <= 100) {
    TailCurrentLimit = analogRead(A2);
  }
  encTail = 0;
  motor(0);

  delay(20000);

}
void loop() {
  if (Serial3.available() != 0) {
    pos = Serial3.read() - 80;
    if ((pos < 0 && pos > -5) || (pos > 0 && pos < 5)) {
      pos = 0;
    }
    if (pos != 0 && pos >= - 65) {
      err = pos - (value / 4);
      i += err * ki;
      u = err * kp + (err - err_old) * kd;
      err_old = err;
      if (u > 40)
        u = 40;
      if (u < -40)
        u = -40;

      motorA.set(u);
      Serial.println(pos);
      if (kar && value / 4 > -5 && value / 4 < 5) {
        motorA.stop();
        playerCrow.play(1);
        delay(1000);
        strela.write(500);
        delay(1000);
        strela.write(90);

        permanentLeds(pinLedEyeLeft, 0x0000FF);
        permanentLeds(pinLedEyeRight, 0x0000FF);

        lidRight.write(50);
        lidLeft.write(130);

        wingTurnL.write(170);
        wingTurnR.write(150);

        hand.write(0);
        opening.write(0);
        delay(1000);
        opening.write(50);
        delay(1000);
        opening.write(0);
        delay(1000);
        opening.write(50);
        delay(1000);
        tailClosed();
        delay(15000);
        kar = false;
      }
      else if (value / 4 > -5 && value / 4 < 5) {
        countFox += 1;
      }

      float ambientTemp = sensor.getAmbientTempCelsius();
      float objectTemp = sensor.getObjectTempCelsius();

      Serial.println();
      if ((ambientTemp > 600 && objectTemp > -60) || (ambientTemp > 24 && objectTemp > 29)) {
        tailOpen();
        hand.write(100);
        permanentLeds(pinLedEyeLeft, 0xFF7700);
        permanentLeds(pinLedEyeRight, 0xFF7700);
        kar = true;
      }
      else {
        handleGesture();
      }
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
