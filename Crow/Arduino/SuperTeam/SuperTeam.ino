#include "motors.h"
#include "APDS9960.h"
#include "MLX90614.h"
#include <stdio.h>
#define timeCode 20

Rotation rot;
Myservo servo;
Tail tail;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial2.begin(9600);
  Serial.flush();
  Serial3.flush();
  led.init_leds();
  init_apds();
  init_player();
  rot.init_motor_rotation();
  rot.init_enc_rotation();
  init_temp();
  tail.init_enc_tail();
  tail.init_motor_tail();
  servo.init_servo();

  servo.basic_servo();
  tail.calibrovka();
  led.permanentLeds(27, 0x050000);
  led.permanentLeds(29, 0x050000);
  //servo.Begin();//*/
}

void loop() {
  float objTemp = objectTemp(), ambTemp = ambientTemp();
  int handle = handleGesture();
  bool kar = ((ambTemp > 600.0 && objTemp >= -7.0)  || (ambTemp > 18.0 && (objTemp - ambTemp) >= 10.0));
  static int count = 0;
  static bool kar0 = false;
  if (kar)
    kar0 = true;
  if (kar0) {
    kar0 = false;
    count++;
    switch (count) {
      case 1:
        led.permanentLeds(27, 0xFF0000);
        led.permanentLeds(29, 0xFF0000);
        playerCrow.play(1);
        for (int i = 0; i < 3; i++) {
          led.permanentLeds(27, 0xFF0000);
          led.permanentLeds(29, 0xFF0000);
          servo.moveLidRight(140);
          servo.moveLidLeft(20);
          delay(600);
          servo.moveLidRight(10);
          servo.moveLidLeft(170);
          led.permanentLeds(27, 0x02F03F);
          led.permanentLeds(29, 0xF077FF);
          delay(600);
        }
        for (int i = 0; i < 3; i++) {
          servo.wingTurnLeft(20);
          servo.wingTurnRight(160);
          delay(700);
          servo.wingTurnRight(110);
          servo.wingTurnLeft(110);
          delay(700);
        }
        break;
      case 2:
        playerCrow.play(2);
        for (int i = 0; i < 3; i++) {
          servo.moveOpening(20);
          delay(400);
          servo.moveOpening(50);
          delay(400);
        }
        rot.motor_rot_set(25);
        delay(2000);
        rot.motor_rot_stop();
        delay(6000);
        rot.motor_rot_set(-25);
        delay(2000);
        rot.motor_rot_stop();
        uint32_t timer = millis();
        while (millis() - timer < 20000) {
          led.changeLeds(27, 0x0B00BB, 5, 200);
        }
        break;
    }
  }
  if (handle == 1) {
    led.permanentLeds(27, 0x00FF00);
    led.permanentLeds(29, 0x00FF00);
    strela.write(500);    //выстрел сыром
    delay(1000);
    strela.write(90);
    for (int i = 0; i < 3; i++) {
      servo.moveLidRight(140);
      servo.moveLidLeft(20);
      delay(600);
      servo.moveLidRight(10);
      servo.moveLidLeft(170);
      delay(600);
    }
    for (int i = 0; i < 2; i++) {
      servo.moveHead(100);
      delay(700);
      servo.moveHead(0);
      delay(700);
    }
  }
}//*/
