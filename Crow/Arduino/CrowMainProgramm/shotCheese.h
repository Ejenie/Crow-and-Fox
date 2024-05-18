Servo strela;

void shotCheese(uint32_t timeShot) {
  uint32_t timerShot = millis();
  while (millis() - timerShot < timeShot) {
    continue;
  }
  strela.write(500);
  delay(1000);
  strela.write(90);
}
