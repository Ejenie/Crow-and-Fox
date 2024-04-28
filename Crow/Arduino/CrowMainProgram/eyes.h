int currentPosition = 0;
const int closeEye = 0;

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
