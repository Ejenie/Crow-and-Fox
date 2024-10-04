#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini playerCrow;

typedef struct {
  int pos;
  int count;
} PosCount;

void init_player() {
  playerCrow.begin(Serial2);  //инициализируем плеер
  playerCrow.volume(30);      //от 10 до 30
}

int myabs(int num) {
  if (num < 0)
    num *= -1;
  return num;
}

PosCount camera() {
  PosCount result;
  if (Serial3.available()) {
    result.pos = Serial3.read();
    static int pos_old = 0;
    result.pos -= 80;
    if (result.pos > 100)
      result.pos = pos_old;
    result.pos = int((result.pos + pos_old) / 2);
    if ((myabs(result.pos) > 0 && myabs(result.pos) < 3) && (myabs(pos_old) > 0 && myabs(pos_old) < 3) && (micros() % 2000) < 1000 && pos_old != result.pos) {
      result.count++;
    }    
    pos_old = result.pos;
  }
  return result;
}
/*int camera() {
  static int pos_old = 0;
  int pos;
  if (Serial3.available()) {
    pos = Serial3.read() - 80;
    pos = int((pos + pos_old) / 2);
    pos_old = pos;
  }
  return pos;
  }*/
float pd_reg(int pos, uint32_t value_conv) {
  static int err = 0, err_old = 0;
  static float u = 0, kp = 1, kd = 1.6, kS = 0.96;
  err = pos - value_conv;
  u = err * kp + (err - err_old) * kd;
  err_old = err;
  if (u > 30)
    u = 30;
  if (u < -30)
    u = -30;
  return u * kS;
}
