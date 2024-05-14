#include <Motors.h>
#include <DFRobot_MLX90614.h>
#include <Servo.h>

#define MLX90614_I2C_ADDR 0x00
DFRobot_MLX90614_I2C sensor(MLX90614_I2C_ADDR, &Wire); 

Motors motorA = Motors(11, 49, 43, 3, 41); //pinPWM, pinA, pinB, interruptNumber, directionPin
Servo strela;

bool direct = true, kar = false;
float kp = 0.70, kd = 0, u = 0;
int i = 0, pos = 0, err_old = 0, vel = 20, err = 0;
uint32_t myTimer = millis();
int32_t value = 0;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
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
      u = err * kp + (err - err_old) * kd;
      err_old = err;
      if (u > 30)
        u = 30;
      if (u < -30)
        u = -30;
      motorA.set(u);
      if (kar && value / 4 > -5 && value / 4 < 5) {
        delay(1000);
        strela.write(500);
        delay(1000);
        strela.write(90);
        motorA.stop();
        delay(15000);
      }
      Serial.print(pos);
      Serial.print("  ");
      Serial.print(value / 5);
      Serial.print("  ");
      Serial.print(err);
      Serial.print("  ");
      Serial.println(u);
      float ambientTemp = sensor.getAmbientTempCelsius();
      float objectTemp = sensor.getObjectTempCelsius();

      //      Serial.print("Ambient celsius : "); Serial.print(ambientTemp); Serial.println(" °C");
      //      Serial.print("Object celsius : ");  Serial.print(objectTemp);  Serial.println(" °C");
      //
      //      Serial.print("Ambient fahrenheit : "); Serial.print(ambientTemp * 9 / 5 + 32); Serial.println(" F");
      //      Serial.print("Object fahrenheit : ");  Serial.print(objectTemp * 9 / 5 + 32);  Serial.println(" F");

      Serial.println();
      if ((ambientTemp > 600 && objectTemp > -90) || (ambientTemp > 24 && objectTemp > 28)) {
        kar = true;
      }
    }
    else
      motorA.stop();
  }
}
