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

void motor (int v1) {
  analogWrite(PWM, (v1 < 0) ? (v1*-1) : v1 = v1);
  if (v1 > 0) {
    digitalWrite(INB, 1);
    digitalWrite(INA, 0);
  }
  if (v1 < 0) {
    digitalWrite(INB, 0);
    digitalWrite(INA, 1);
  }
  if (v1 == 0) {
    digitalWrite(INB, 1);
    digitalWrite(INA, 1);
  }
}
