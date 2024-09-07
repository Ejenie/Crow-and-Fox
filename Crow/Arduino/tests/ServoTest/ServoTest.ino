#include <Servo.h>

#include "eyes.h"
#include "hand.h"
#include "wings.h"
#include "shotCheese.h"

#define pinServoEyeLeft 13
#define pinServoEyeRight 35
#define pinServoWingPlaneLeft 9
#define pinServoWingPlaneRight 46
#define pinServoWingTurnRight 6
#define pinServoWingTurnLeft 5
#define pinServoStrela 48
#define pinServoHand 8
#define pinServoOpening 7

void test() {
  lidLeft.write(60);
  delay(200);
  lidLeft.write(120);
  delay(200);

  lidRight.write(60);
  delay(200);
  lidRight.write(120);
  delay(200);

  wingTurnL.write(60);
  delay(200);
  wingTurnL.write(120);
  delay(200);

  wingTurnR.write(60);
  delay(200);
  wingTurnR.write(120);
  delay(200);

  wingPlaneL.write(60);
  delay(200);
  wingPlaneL.write(120);
  delay(200);

  wingPlaneR.write(60);
  delay(200);
  wingPlaneR.write(120);
  delay(200);

  strela.write(60);
  delay(200);
  strela.write(120);
  delay(200);

  hand.write(60);
  delay(200);
  hand.write(120);
  delay(200);

  opening.write(60);
  delay(200);
  opening.write(120);
  delay(200);
}

void setup() {
  lidLeft.attach(pinServoEyeLeft);    //инициализация серво-моторов
  lidRight.attach(pinServoEyeRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  wingPlaneL.attach(pinServoWingPlaneLeft);
  wingPlaneR.attach(pinServoWingPlaneRight);

  strela.attach(pinServoStrela);

  hand.attach(pinServoHand);
  opening.attach(pinServoOpening);
}

void loop() {
  wingPlaneLeft(10);
  delay(600);
}
