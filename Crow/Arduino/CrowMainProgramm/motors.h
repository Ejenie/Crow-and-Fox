Motors motorA = Motors(11, 49, 43, 3, 41);    //pinPWM, pinA, pinB, interruptNumber, directionPin

int32_t value = 0;
int pinPWM = 41;

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

void ann_enc(int pinINTER) {
  attachInterrupt(digitalPinToInterrupt(pinINTER), enc, RISING);
}
