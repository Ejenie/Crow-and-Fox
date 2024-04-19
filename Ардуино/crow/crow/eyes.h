int currentPosition = 0;
const int closeEye = 0;

Servo lidLeft;
Servo lidRight;

void moveEyes(int desiredPosition) {

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  lidLeft.write(- (closeEye - currentPosition));
  lidRight.write(closeEye - currentPosition);
}


