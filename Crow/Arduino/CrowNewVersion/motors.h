#include <Motors.h>

#define CLK 2
#define DT 40
#define CLKX 3
#define DTX 41

#define INB 31
#define INA 39
#define PWM 10

Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin

void init_motor_rotation() {
  pinMode(DTX, INPUT);
  pinMode(CLKX, INPUT);
}

void init_motor_tail() {
  pinMode(PWM, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INA, OUTPUT);
}
void init_enc_rotation() {
  attachInterrupt(digitalPinToInterrupt(3), ann_enc, RISING);
}

int32_t value = 0;

void ann_enc() {
  if (digitalRead(DTX))
    value--;
  else
    value++;
}
