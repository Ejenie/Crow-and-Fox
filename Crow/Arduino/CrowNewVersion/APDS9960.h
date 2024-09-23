#include <Wire.h>                             // Подключаем библиотеку Wire
#include <SparkFun_APDS9960.h>                // Подключаем библиотеку SparkFun_APDS9960

int isr_flag = 0;
void interruptRoutine() {
  isr_flag = 1;
}

void init_handleGesture() {
  SparkFun_APDS9960 apds = SparkFun_APDS9960(); // Создаем объект
  attachInterrupt(1, interruptRoutine, FALLING);    //прерывание датчика жестов на спад
}
