//#include "APDS9960.h"
#include "MLX90614.h"
#include "encoder.h"
#include "leds.h"
#include "servo.h"
#define timeCode 20000

Leds led;
Rotation rot;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  led.init_leds();
  init_player();
  rot.init_motor_rotation();
  rot.init_enc_rotation();
  //init_temp();
  //init_enc_rotation();
  init_enc_tail();
  //init_leds();
  //init_motor_rotation();
  init_motor_tail();
  init_servo();

  basic_servo();
}

void loop() {
  /*static uint32_t timerCode = millis();
    while (millis() - timerCode < timeCode)
    ;
    timerCode = millis();*/
  int pos = camera();
  float u = rot.turn_fox(pos);
  rot.motor_rot_set(u);
}
