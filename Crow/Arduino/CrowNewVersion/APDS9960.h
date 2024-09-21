#include <Wire.h>                             // Подключаем библиотеку Wire
#include <SparkFun_APDS9960.h>                // Подключаем библиотеку SparkFun_APDS9960

SparkFun_APDS9960 apds = SparkFun_APDS9960(); // Создаем объект

void init_handleGesture() {
  attachInterrupt(1, interruptRoutine, FALLING);    //прерывание датчика жестов на спад
}
