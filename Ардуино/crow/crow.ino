#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include <FastLED.h>
#include <DFRobot_MLX90614.h>
#include <Motors.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
//блютуууууууууууууууууууууууз

#define CLOSE_LEFT_EYE 60
#define CLOSE_RIGHT_EYE 0
#define DELTA_EYE 60


#define INTR_PIN 2 // порт прерывания
SparkFun_APDS9960 apds = SparkFun_APDS9960(); // создаем объект apds

Servo tail;
Servo wing_Left;
Servo wing_Right;
Servo lid_Left;
Servo lid_Right;
Servo cheese;
Servo opening;

DFRobotDFPlayerMini myDFPlayer;

DFRobot_MLX90614_I2C sensor(0x00, &Wire);

Motors motorA = Motors(10, 23, 22, 0, 48); //pinPWM, pinA, pinB, interruptNumber, directionPin

int condition;
int isr_flag = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);    //камера
  Serial3.begin(9600);    //плеер

  sensor.setEmissivityCorrectionCoefficient(1.0);
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);

  sensor.enterSleepMode();  //импульс датчика тепла
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);


  // инициализируем прерывание на спад
  attachInterrupt(1, interruptRoutine, FALLING);  //прерывание датчика жестов
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
