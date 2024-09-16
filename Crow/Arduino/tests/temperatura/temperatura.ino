/*!
   @file        getData.ino
   @brief       this demo demonstrates how to put the sensor enter/exit sleep mode and get temperature data measured by sensor
   @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @license     The MIT License (MIT)
   @author      [qsjhyy](yihuan.huang@dfrobot.com)
   @version     V1.0
   @date        2021-08-09
   @url         https://github.com/DFRobot/DFRobot_MLX90614
*/
#include <DFRobot_MLX90614.h>
#include <Wire.h>

DFRobot_MLX90614_I2C sensor(0x00, &Wire);

void setup()
{
  Serial.begin(9600);
  while (NO_ERR != sensor.begin()) {    //выявление ошибок в подключении датчика тепла
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
  sensor.setEmissivityCorrectionCoefficient(1.0);
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);


  sensor.enterSleepMode();    //импульс датчика тепла
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);
}

void loop()
{
  /**
     get ambient temperature, unit is Celsius
     return value range： -40.01 °C ~ 85 °C
  */
  float ambientTemp = sensor.getAmbientTempCelsius();

  /**
     get temperature of object 1, unit is Celsius
     return value range：
     @n  -70.01 °C ~ 270 °C(MLX90614ESF-DCI)
     @n  -70.01 °C ~ 380 °C(MLX90614ESF-DCC)
  */
  float objectTemp = sensor.getObjectTempCelsius();

  // print measured data in Celsius
  Serial.print("Ambient celsius : "); Serial.print(ambientTemp); Serial.println(" °C");
  Serial.print("Object celsius : ");  Serial.print(objectTemp);  Serial.println(" °C");
  Serial.println();
  delay(500);
}
