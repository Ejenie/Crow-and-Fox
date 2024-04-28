#define CLOSE_LEFT_WING 0
#define CLOSE_RIGHT_WING 0

Servo wingL;
Servo wingR;

void wingLeft(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  wingL.write(CLOSE_LEFT_WING - currentPosition);
}

void wingRight(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  wingR.write(CLOSE_RIGHT_WING - currentPosition);
}
