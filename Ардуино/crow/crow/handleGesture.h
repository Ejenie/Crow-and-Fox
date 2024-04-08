#include <SparkFun_APDS9960.h>
#define INTR_PIN 2    // порт прерывания датчика  жестов

SparkFun_APDS9960 apds = SparkFun_APDS9960();   // создаем объект датчика жестов


bool isr_flag = false;

void interruptRoutine() {
  isr_flag = true;
}

void ann_handleGesture() {
  attachInterrupt(1, interruptRoutine, FALLING);    //прерывание датчика жестов на спад
}
 
void handleGesture() {
    if (apds.isGestureAvailable() ) {
    switch (apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}
