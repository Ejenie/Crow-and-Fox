#include <Servo.h>
#define pinServoEyeLeft 13
#define pinServoEyeRight 35
#define pinServoWingPlaneLeft 9
#define pinServoWingPlaneRight 46
#define pinServoWingTurnRight 6
#define pinServoWingTurnLeft 5
#define pinServoStrela 48
#define pinServoHand 8
#define pinServoOpening 7

Servo lidLeft;
Servo lidRight;
Servo opening;
Servo head;
Servo strela;
Servo wingTurnL;
Servo wingTurnR;
Servo wingPlaneL;
Servo wingPlaneR;

void init_servo() {
  lidLeft.attach(pinServoEyeLeft);    //инициализация серво-моторов
  lidRight.attach(pinServoEyeRight);

  wingTurnL.attach(pinServoWingTurnLeft);
  wingTurnR.attach(pinServoWingTurnRight);

  wingPlaneL.attach(pinServoWingPlaneLeft);
  wingPlaneR.attach(pinServoWingPlaneRight);

  strela.attach(pinServoStrela);

  head.attach(pinServoHand);
  opening.attach(pinServoOpening);
}

void basic_servo() {
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
}
