#include <Wire.h>
#include <DFRobot_MLX90614.h>

DFRobot_MLX90614_I2C sensor(0x00, &Wire);

void ann_wire() {
  sensor.setEmissivityCorrectionCoefficient(1.0);   //настройки датчика тепла
  sensor.setI2CAddress(0x00);
  sensor.setMeasuredParameters(sensor.eIIR100, sensor.eFIR1024);

  sensor.enterSleepMode();    //импульс датчика тепла
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);
}
