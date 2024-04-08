#define CLOSE_EYE 0

Servo lids;

void eyes(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lids.write(CLOSE_EYE - currentPosition);
}
