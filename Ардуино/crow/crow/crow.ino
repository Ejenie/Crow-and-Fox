#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include <FastLED.h>
#include <DFRobot_MLX90614.h>
#include <Motors.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

#define INTR_PIN 2    // порт прерывания датчика жестов

Servo tail;
Servo wing_Left;
Servo wing_Right;
Servo lid_Left;
Servo lid_Right;
Servo cheese;
Servo opening;
Servo hand;

DFRobotDFPlayerMini myDFPlayer;
DFRobot_MLX90614_I2C sensor(0x00, &Wire);
Motors motorA = Motors(10, 23, 22, 0, 48);    //pinPWM, pinA, pinB, interruptNumber, directionPin
SparkFun_APDS9960 apds = SparkFun_APDS9960();   // создаем объект датчика жестов

int condition;
bool isr_flag = false;
String message; // строка для входящих сообщений блютуз

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);    //блютуз
  Serial2.begin(9600);    //камера
  Serial3.begin(9600);    //плеер

  sensor.setEmissivityCorrectionCoefficient(1.0);   //настройки датчика тепла
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);

  sensor.enterSleepMode();    //импульс датчика тепла
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);

  attachInterrupt(1, interruptRoutine, FALLING);    //прерывание датчика жестов на спад
}

void loop() {
  switch (condition) {
    case 0:   //сидит на дереве, держит сыр
    case 1:   //Ворона поворачивается в сторону Лисицы (движения Вороны изображающие радость),всё ещё держит сыр
      if (Serial2.available() > 0) {
        int pos = Serial2.read();
        Serial.print(nMotorEncoder[0]);   //оно еще не работает, но я допишу
        Serial.print("  ");
        Serial.print(nMotorEncoder[1]);
        Serial.print("  ");
        Serial.print(nMotorEncoder[2]);
        Serial.print("  ");
        Serial.println(nMotorEncoder[3]);
        motorA.set(pos);
      }
      break;
    case 2:   //Ворона открывает клюв, сыр выбрасывается к Лисице
      break;
    case 3:   //Ворона сидит без сыра, грутсно опустив голову. При поглажеваниях ее головы, шевелит крыльями и веками глаз
      break;
    default: break;
  }
}
