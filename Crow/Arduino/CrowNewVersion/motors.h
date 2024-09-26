#include <Motors.h>
#include "other.h"

#define CLK 2
#define DT 40
#define CLKX 3
#define DTX 41

#define INB 31
#define INA 39
#define PWM 10

int32_t value = 0;
void ann_enc() {
  if (digitalRead(DTX))
    value--;
  else
    value++;
}

class Rotation {
  private:
    Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin
  public:
    void init_motor_rotation() {
      pinMode(DTX, INPUT);
      pinMode(CLKX, INPUT);
    }
    void init_enc_rotation() {
      attachInterrupt(digitalPinToInterrupt(CLKX), ann_enc, RISING);
    }
    void motor_rot_stop() {   //+
      motorA.stop();
    }
    void motor_rot_begin(int v) {   //+
      motorA.set(v);
    }
    void turn_fox() {
      int pos = camera();
      if (pos){
        float u = pd_reg(pos, value / 4);
        motor_rot_begin(u);
      }
      else {
        motor_rot_stop();
      }
    }
};

void init_motor_tail() {
  pinMode(PWM, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INA, OUTPUT);
}

void motor (int v1) {
  analogWrite(PWM, (v1 < 0) ? (v1 * -1) : v1 = v1);
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
