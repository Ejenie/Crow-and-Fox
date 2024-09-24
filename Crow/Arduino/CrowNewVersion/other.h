#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini playerCrow;

void init_player() {
  playerCrow.begin(Serial2);  //инициализируем плеер
  playerCrow.volume(30);      //от 10 до 30
}
