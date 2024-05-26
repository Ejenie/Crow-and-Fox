#include <Motors.h>
#include <DFRobot_MLX90614.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

#define MLX90614_I2C_ADDR 0x00
DFRobot_MLX90614_I2C sensor(MLX90614_I2C_ADDR, &Wire);

Motors motorA = Motors(11, 49, 43, 3, 41); //pinPWM, pinA, pinB, interruptNumber, directionPin
Servo strela;

DFRobotDFPlayerMini playerCrow;

bool direct = true, kar = false;
float kp = 0.7, kd = 2, u = 0, i = 0, ki = 0.001;
int pos = 0, err_old = 0, vel = 20, err = 0;
uint32_t myTimer = millis();
int32_t value = 0;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.println("Hello");
  Serial2.begin(9600);
  playerCrow.begin(Serial2);  //инициализируем плеер
  playerCrow.volume(30);      //от 10 до 30
  pinMode(41, INPUT);
  pinMode(3, INPUT);
  strela.attach(48);
  attachInterrupt(digitalPinToInterrupt(3), enc, RISING);
  myTimer = millis();

  while ( NO_ERR != sensor.begin() ) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
  sensor.setEmissivityCorrectionCoefficient(1.0);
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);


  sensor.enterSleepMode();
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);

}

void loop() {
  if (Serial3.available() != 0) {
    pos = Serial3.read() - 80;

    if ((pos < 0 && pos > -5) || (pos > 0 && pos < 5)) {
      pos = 0;
    }
    if (pos != 0)  {
      err = pos - (value / 4);
      i += err * ki;
      if (abs(i) > 5)
        i = 5 * sign(i);
      u = err * kp + (err - err_old) * kd;
      err_old = err;
      if (u > 40)
        u = 40;
      if (u < -40)
        u = -40;

      motorA.set(u);

      float ambientTemp = sensor.getAmbientTempCelsius();
      float objectTemp = sensor.getObjectTempCelsius();

      if (((ambientTemp > 600 && objectTemp > -60) || (ambientTemp > 24 && objectTemp > 29)) && value / 4 > -5 && value / 4 < 5) {
        Serial.println("temp");
        delay(1000);
        playerCrow.play(1);
        strela.write(500);
        delay(1000);
        strela.write(90);
        motorA.stop();
        delay(15000);
      }
      /*Serial.print(pos);
        Serial.print("  ");
        Serial.print(value / 4);
        Serial.print("  ");
        Serial.print(err);
        Serial.print("  ");
        Serial.println(u);*/

      Serial.println();
      if ((ambientTemp > 600 && objectTemp > -90) || (ambientTemp > 24 && objectTemp > 28)) {
        //kar = true;
      }
    }
    else
      motorA.stop();
  }
}
