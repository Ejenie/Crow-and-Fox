#include <Servo.h>

Servo lidLeft;
Servo lidRight;

int pos = 0;
uint32_t timeEyeLeft = millis();
uint32_t timeEyeRight = millis();


void setup() {
  lidLeft.attach(7);  // attaches the servo on pin 9 to the servo object
  lidRight.attach(6);
}
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

void loop() {
  moveEyeLeft();
  moveEyeRight();
}
