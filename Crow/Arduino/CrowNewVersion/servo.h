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

typedef struct {
  int wTr;
  int wTl;
  int wPr;
  int wPl;
  int mLr;
  int mLl;
  int mH;
  int mO;
} ServoPos;

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
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        wingTurnR.write(currentPosition);
    }

    void wingTurnLeft(int desiredPosition) {
      static int currentPosition = 0;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        wingTurnL.write(currentPosition);
    }

    void wingPlaneRight(int desiredPosition) { //max - 120 min - 80
      static int currentPosition = 180;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        wingPlaneR.write(currentPosition);
    }

    void wingPlaneLeft(int desiredPosition) { //max - 120 min - 80
      static int currentPosition = 0;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        wingPlaneL.write(currentPosition);
    }

    void moveLidLeft(int desiredPosition) {
      static int currentPosition = 0;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        lidLeft.write(currentPosition);
    }

    void moveLidRight(int desiredPosition) {
      static int currentPosition = 90;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        lidRight.write(currentPosition);
    }

    void moveHead(int desiredPosition) {
      static int currentPosition = 0;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        head.write(currentPosition);
    }

    void moveOpening(int desiredPosition) {
      static int currentPosition = 0;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        opening.write(currentPosition);
    }

    void moveStrela(int desiredPosition) {
      static int currentPosition = 0;
      uint32_t timer = millis();

      while (currentPosition > desiredPosition)
        currentPosition -= 1;
      while (currentPosition < desiredPosition)
        currentPosition += 1;
      if (millis() - timer < 20)
        strela.write(currentPosition);
    }

    void basic_servo() {
      uint32_t timerServo = millis();
      if (millis() - timerServo < 20) {
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
    void Begin() {
      static uint32_t timerBegin = millis();
      while (millis() - timerBegin < 23000) {
        if (millis() % 4600 < 2800) {
          for (int i = 0; i < 3; i++) {
            if (millis() % 800 < 400) {
              moveOpening(20);
            }
            else if (millis() % 800 < 800) {
              moveOpening(50);
            }
          }
        }
      }
    }
    ServoPos positionServo(int countFox) { //, bool kar, bool flagKar) {
      ServoPos result;
      switch (countFox) {
        case 3:
          for (int i = 0; i < 3; i++) {
            if (millis() % 1400 < 700) {
              result.mH = 100;
            }
            else if (millis() % 1400 < 1400) {
              result.mH = 0;
            }
          }
          if (millis() % 1000 < 500) {
            result.mLr = 140;
            result.mLl = 30;
          }
          else if (millis() % 1000 < 1000) {
            result.mLr = 10;
            result.mLl = 170;
          }
          break;
        case 5:
          for (int i = 0; i < 3; i++) {
            if (millis() % 1200 < 600) {
              result.wTr = 20;
              result.wTl = 160;
            }
            else if (millis() % 1200 < 1200) {
              result.wTr = 110;
              result.wTl = 110;
            }
          }
          break;
      }
      /*if (kar) {
        result.wPr = 90;
        result.wPl = 90;
        }
        if (flagKar) {
        //флаг стрелы
        result.mLr = 140;
        result.mLl = 20;
        result.mH = 0;
        result.mO = 50;
        result.wTr = 90;
        result.wTl = 150;
        //придумать
        }*/
      return result;
    }
};
