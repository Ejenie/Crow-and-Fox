#include "motors.h"

int32_t value = 0;
void ann_enc() {
  if (digitalRead(DTX))
    value--;
  else
    value++;
}

int32_t encTail = 0;
void isrTail() {
  if (digitalRead(DT))
    encTail++;
  else
    encTail--;
}

void init_enc_rotation() {
  attachInterrupt(digitalPinToInterrupt(CLKX), ann_enc, RISING);
}
void init_enc_tail() {
  attachInterrupt(digitalPinToInterrupt(CLK), isrTail, RISING);
}
