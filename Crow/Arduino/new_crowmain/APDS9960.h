#include <Wire.h>                             // Подключаем библиотеку Wire
#include <SparkFun_APDS9960.h>                // Подключаем библиотеку SparkFun_APDS9960

int isr_flag = 0;

SparkFun_APDS9960 apds = SparkFun_APDS9960(); // Создаем объект

void interruptRoutine() {
  isr_flag = 1;
}
