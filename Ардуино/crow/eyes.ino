void eyeLeft(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lid_Left.write(CLOSE_LEFT_EYE - currentPosition);
}

void eyeRight(int desiredPosition) {
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lid_Right.write(CLOSE_RIGHT_EYE + currentPosition);
}
