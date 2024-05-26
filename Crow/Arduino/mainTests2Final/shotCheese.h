Servo strela;

void shotCheese(uint32_t timeShot) {
  uint32_t timerShot = millis();
  if (millis() - timerShot > timeShot) {
    strela.write(500);
    delay(1000);
    strela.write(90);
  }
}
