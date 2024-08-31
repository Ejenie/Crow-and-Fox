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

int pos = 0;    // variable to store the servo position

void test() {
  //pass
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
  for (int i = 0; i < 2; i++) {
    wingTurnLeft(20);
    delay(600);
    wingTurnLeft(150);
    delay(600);
  }
}
