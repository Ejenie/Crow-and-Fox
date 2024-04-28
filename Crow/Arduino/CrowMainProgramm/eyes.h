int currentPosition = 0;
const int closeEye = 0;

uint32_t timeEyeLeft = millis();
uint32_t timeEyeRight = millis();

Servo lidLeft;
Servo lidRight;

void moveLidLeft(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lidLeft.write(currentPosition);
}

void moveLidRight(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lidRight.write(currentPosition);
}


void moveEyeLeft() {
  if (millis() - timeEyeLeft > 15) {
    timeEyeLeft = millis();
    if (millis() % 6000 > 2700)
      moveLidLeft(120);
    else if (millis() % 6000 > 150)
      moveLidLeft(40);
  }
}

void moveEyeRight() {
  if (millis() - timeEyeRight > 15) {
    timeEyeRight = millis();
    if (millis() % 6000 > 2700)
      moveLidRight(40);
    else if (millis() % 6000 > 150)
      moveLidRight(120);
  }
}
