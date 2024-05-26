int32_t value = 0;

Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(10, 39, 31, 2, 40);  //pinPWM, pinA, pinB, interruptNumber, directionPin

void enc() {
  if (digitalRead(41))
    value--;
  else
    value++;
}
