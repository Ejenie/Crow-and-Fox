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

class Myservo {
  private:
    Servo lidLeft;
    Servo lidRight;
    Servo opening;
    Servo head;
    Servo strela;
    Servo wingTurnL;
    Servo wingTurnR;
    Servo wingPlaneL;
    Servo wingPlaneR;
  public:
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

    void wingTurnRight(int desiredPosition) {
      static int currentPosition = 180;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      wingTurnR.write(currentPosition);
    }

    void wingTurnLeft(int desiredPosition) {
      static int currentPosition = 0;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      wingTurnL.write(currentPosition);
    }

    void wingPlaneRight(int desiredPosition) { //max - 120 min - 80
      static int currentPosition = 180;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      wingPlaneR.write(currentPosition);
    }

    void wingPlaneLeft(int desiredPosition) { //max - 120 min - 80
      static int currentPosition = 0;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      wingPlaneL.write(currentPosition);
    }

    void moveLidLeft(int desiredPosition) {
      static int currentPosition = 0;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      lidLeft.write(currentPosition);
    }

    void moveLidRight(int desiredPosition) {
      static int currentPosition = 90;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      lidRight.write(currentPosition);
    }
    
    void moveHead(int desiredPosition) {
      static int currentPosition = 0;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      head.write(currentPosition);
    }

    void moveOpening(int desiredPosition) {
      static int currentPosition = 0;

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;

      opening.write(currentPosition);
    }

    void basic_servo() {
      uint32_t timerServo = millis();
      if (millis() - timerServo < 200) {
        wingTurnLeft(10);    //от 10 до 160
        wingTurnRight(170);   //от 170 до 70

        wingPlaneLeft(10);
        wingPlaneRight(170);

        moveLidLeft(170);
        moveLidRight(10);

        moveHead(0);
        moveOpening(20);
      }
    }
   /* void strela(bool flagStrela) {
      if (flagStrela) {
        strela.write(500);
        uint32_t timerStrela = millis();
        if (millis() - timerStrela > 1000)
          strela.write(90);
      }
    }*/
};
