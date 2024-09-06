#include "eyes.h"
#include "wire.h"
#include "head.h"
#include "motors.h"
#include "leds.h"
#include "wings.h"
#include "turnForFox.h"
#include "shotCheese.h"
#include "APDS9960.h"
#include "tail.h"
#include "declaring.h"

void handleGesture() {    //функция состояний датчика жестов
  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:    //движение рукой вверх: запасной вариант при отказе датчика тепла
        Serial.println("zhest");
        motorA.stop();
        tailOpen();
        head.write(100);
        permanentLeds(pinLedEyeLeft, 0xFF7700);
        permanentLeds(pinLedEyeRight, 0xFF7700);
        kar = true;
        break;

      case DIR_DOWN:    //движение рукой вниз: финальные действия Вороны
        motorA.stop();
        Serial.println("down");
        permanentLeds(pinLedEyeLeft, 0xFF2277);
        permanentLeds(pinLedEyeRight, 0xFF2277);

        for (int i = 0; i < 3; i++) {
          lidRight.write(140);
          lidLeft.write(30);
          delay(500);
          lidRight.write(10);
          lidLeft.write(170);
          delay(500);
        }
        for (int i = 0; i < 3; i++) {
          wingTurnLeft(70);
          wingTurnRight(50);
          delay(700);
          wingTurnRight(70);
          wingTurnLeft(50);
          delay(700);
        }
        wingTurnLeft(90);
        wingTurnRight(90);
        tailOpen();
        delay(2000);
        for (int i = 0; i < 5; i++) {
          motorA.set(25);
          delay(3000);
          motorA.set(-25);
          delay(3000);
        }
        motorA.stop();
        tailClosed();
        break;
      default:
        Serial.println("NONE");
    }
  }
}
