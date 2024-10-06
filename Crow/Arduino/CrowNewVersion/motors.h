#include <Motors.h>
#include "other.h"
#include "servo.h"

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
    void motor_rot_set(int v) {   //+
      motorA.set(v);
    }
    float turn_fox(int pos) {
      if (pos) {
        return pd_reg(pos, value / 4);
      }
      else {
        return 0;
      }
    }
    int need_for_a_motor(bool flagKar, int pos) {
      if (!flagKar) {
        return turn_fox(pos);
      }
      else{
        return 0;
      }
    }
};

int32_t encTail = 0;
void isrTail() {
  if (digitalRead(DT))
    encTail++;
  else
    encTail--;
}
class Tail {
  private:
    int tail_lim = 6000;
    int tail_Clos = 10;
  public:
    void init_motor_tail() {
      pinMode(PWM, OUTPUT);
      pinMode(INB, OUTPUT);
      pinMode(INA, OUTPUT);
    }
    void init_enc_tail() {
      attachInterrupt(digitalPinToInterrupt(CLK), isrTail, RISING);
    }
    void motor_tail (int v1) {
      analogWrite(PWM, myabs(v1));
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
    void tailOpen(bool flag) {
      if (flag) {
        while (myabs(encTail) < tail_lim)
          motor_tail(-20);
        while (myabs(encTail) > tail_lim)
          motor_tail(190);
        motor_tail(0);
      }
    }
    void tailClosed() {
      while (myabs(encTail) > tail_Clos) {
        motor_tail(190);
      }
      while (myabs(encTail) < tail_Clos) {
        motor_tail(-20);
      }
      motor_tail(0);
    }
    void calibrovka() {
      int tailCurrentLimit = 0;
      motor_tail(130);
      delay(130);
      while (tailCurrentLimit <= 100) {
        tailCurrentLimit = analogRead(A2);
        Serial.println("tail");
        Serial.println(tailCurrentLimit);
      }
      encTail = 0;
      motor_tail(0);
    }
};
