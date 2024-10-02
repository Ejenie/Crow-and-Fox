//#include "APDS9960.h"
#include "MLX90614.h"
#include "leds.h"
#include "servo.h"
#include "motors.h"
#define timeCode 20

Leds led;
Rotation rot;
Myservo servo;
Tail tail;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  led.init_leds();
  init_player();
  rot.init_motor_rotation();
  rot.init_enc_rotation();
  init_temp();
  tail.init_enc_tail();
  tail.init_motor_tail();
  servo.init_servo();

  servo.basic_servo();
}

void loop() {
  static uint32_t timerCode = millis();
  while (millis() - timerCode < timeCode);
  timerCode = millis();

  PosCount fox = camera();
  int pos = fox.pos, countFox = fox.count;
  float objTemp = objectTemp(), ambTemp = ambientTemp();

  float u = rot.turn_fox(pos);

  rot.motor_rot_set(u);
}
