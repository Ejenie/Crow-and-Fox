#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini playerCrow;

void init_player() {
  playerCrow.begin(Serial2);  //инициализируем плеер
  playerCrow.volume(30);      //от 10 до 30
}

int camera() {
  static int pos = 0, pos_old = 0;
  if (Serial3.available()) {
    pos = Serial3.read() - 80;
    pos = int((pos + pos_old) / 2);
    pos_old = pos;
  }
  return pos;
}
float pd_reg(int pos, uint32_t value_conv) {
  static int err = 0, err_old = 0;
  static float u = 0, kp = 1, kd = 1.6;
  err = pos - value_conv;
  u = err * kp + (err - err_old) * kd;
  err_old = err;
  if (u > 30)
    u = 30;
  if (u < -30)
    u = -30;
  return u;
}
