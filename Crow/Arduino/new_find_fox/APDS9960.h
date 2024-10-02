#include <Wire.h>                             // Подключаем библиотеку Wire
#include <SparkFun_APDS9960.h>                // Подключаем библиотеку SparkFun_APDS9960

int isr_flag = 0;

SparkFun_APDS9960 apds = SparkFun_APDS9960(); // Создаем объект

void interruptRoutine() {
  isr_flag = 1;
}
int handleGesture() {    //функция состояний датчика жестов
  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:    //движение рукой вверх: запасной вариант при отказе датчика тепла
        return 1;
        break;
      case DIR_DOWN:    //движение рукой вниз: финальные действия Вороны
        return 2;
        break;
      case DIR_LEFT:    //движение рукой вверх: запасной вариант при отказе датчика тепла
        return 3;
        break;
      default:
        return 0;
    }
  }
}
