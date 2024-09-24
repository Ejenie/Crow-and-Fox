//#include "APDS9960.h"
#include "MLX90614.h"
#include "encoder.h"
#include "leds.h"
#include "servo.h"
#include "other.h"
#define timeCode 5000

void setup() {
  Serial.begin(9600);
  init_player();
  init_temp();
  init_enc_rotation();
  init_enc_tail();
  init_leds();
  init_motor_rotation();
  init_motor_tail();
  init_servo();
}

void loop() {
  static uint32_t timer = millis();
  playerCrow.play(1);   //КАР!
  Serial.print(millis() - timer);
  delay(10000);
}
