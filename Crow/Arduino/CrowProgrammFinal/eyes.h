uint32_t timeEyeLeft = millis();
uint32_t timeEyeRight = millis();

Servo lidLeft;
Servo lidRight;

void moveLidLeft(int desiredPosition) {
  static int currentPosition = 0;

  while (currentPosition > desiredPosition)
    currentPosition -= 1;
 while (currentPosition < desiredPosition)
    currentPosition += 1;

  lidLeft.write(currentPosition);
}

void moveLidRight(int desiredPosition) {
  static int currentPosition = 90;

  while (currentPosition > desiredPosition)
    currentPosition -= 1;
  while (currentPosition < desiredPosition)
    currentPosition += 1;

  lidRight.write(currentPosition);
}
