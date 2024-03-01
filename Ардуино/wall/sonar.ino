int sonar() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  uint32_t duration = pulseIn(PIN_ECHO, HIGH);
  uint32_t cm = duration / 58;

  return cm;
}
