#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include <FastLED.h>
#include <DFRobot_MLX90614.h>
#include <Motors.h>
//блютуууууууууууууууууууууууз

#define CLOSE_LEFT_EYE 60
#define CLOSE_RIGHT_EYE 0
#define DELTA_EYE 60

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

void eyeLeft(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lid_Left.write(CLOSE_LEFT_EYE - currentPosition);
}

void eyeRight(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lid_Right.write(CLOSE_RIGHT_EYE + currentPosition);
}
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);    //камера
  Serial3.begin(9600);    //плеер

  sensor.setEmissivityCorrectionCoefficient(1.0);
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);

  sensor.enterSleepMode();  //импульс
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);
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
  }
}
