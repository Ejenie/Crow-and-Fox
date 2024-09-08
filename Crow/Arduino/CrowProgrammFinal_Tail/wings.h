Servo wingTurnL;
Servo wingTurnR;

Servo wingPlaneL;
Servo wingPlaneR;

void wingTurnRight(int desiredPosition) {
  static int currentPosition = 180;

  while (currentPosition > desiredPosition)
    currentPosition -= 1;
  while (currentPosition < desiredPosition)
    currentPosition += 1;

  wingTurnR.write(currentPosition);
}

void wingTurnLeft(int desiredPosition) {
  static int currentPosition = 0;

  while (currentPosition > desiredPosition)
    currentPosition -= 1;
  while (currentPosition < desiredPosition)
    currentPosition += 1;

  wingTurnL.write(currentPosition);
}

void wingPlaneRight(int desiredPosition) { //max - 120 min - 80
  static int currentPosition = 180;

  while (currentPosition > desiredPosition)
    currentPosition -= 1;
  while (currentPosition < desiredPosition)
    currentPosition += 1;

  wingPlaneR.write(currentPosition);
}

void wingPlaneLeft(int desiredPosition) { //max - 120 min - 80
  static int currentPosition = 0;

  while (currentPosition > desiredPosition)
    currentPosition -= 1;
  while (currentPosition < desiredPosition)
    currentPosition += 1;

  wingPlaneL.write(currentPosition);
}
