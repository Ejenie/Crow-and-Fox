Motors motorA = Motors(10, 23, 22, 5, 48);    //pinPWM, pinA, pinB, interruptNumber, directionPin

int32_t value = 0;
int pinPWM = 48;

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
  attachInterrupt(pinINTER, enc, RISING);
}
