Motors motorA = Motors(11, 49, 43, 3, 41);    //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 49, 43, 3, 41);    //pinPWM, pinA, pinB, interruptNumber, directionPin

int32_t value = 0, valueTail = 0;
int pinPWM = 41, pinPWMTail = 34;

void ann_motor(int pinPWM, int pinDIG) {
  pinMode(pinPWM, INPUT);
  pinMode(pinDIG, INPUT);
}

void enc() {
  if (digitalRead(&pinPWM))
    ++value;
  else
    --value;
}

void encTail() {
  if (digitalRead(&pinPWMTail))
    ++valueTail;
  else
    --valueTail;
}
