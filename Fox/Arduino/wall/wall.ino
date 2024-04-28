#define PIN_TRIG 10
#define PIN_ECHO 11

int vel = 120, err, upr;
float kprop = 0.7, kdef = 1;
int sens = 0, sensOld = 0;
float k_filtr = 0.3;
uint32_t timerW = millis(), timerW0 = millis(), value, timerW2 = millis();
bool flag = false;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(1, enc, RISING);
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  while (millis() - timerW0 < 15700) {
    Serial.println(value);
    sens = analogRead(A4);
    Serial.println(sens);
    upr = (400 - sens) * kprop + (sens - sensOld) * kdef;
    if (upr > 40)
      upr = 40;
    else if (upr < -40)
      upr = -40;
    sensOld = sens;
    motor(vel - upr, vel + upr);
  }
  motor(0, 0);
  delay(1000);
  timerW = millis();
  while (millis() - timerW < 5500) {
    Serial.println(value);
    /*if (flag)
      sens = analogRead(A3);
      else*/
    sens = analogRead(A4);
    Serial.println(sens);
    upr = (400 - sens) * kprop + (sens - sensOld) * kdef;
    if (upr > 40)
      upr = 40;
    else if (upr < -40)
      upr = -40;
    sensOld = sens;
    motor(vel - upr, vel + upr);
  }
  povorot();
  timerW2 = millis();
  while (millis() - timerW2 < 5500) {
    Serial.println(value);
    /*if (flag)
      sens = analogRead(A3);
      else*/
    sens = analogRead(A3);
    Serial.println(sens);
    upr = (400 - sens) * kprop + (sens - sensOld) * kdef;
    if (upr > 40)
      upr = 40;
    else if (upr < -40)
      upr = -40;
    sensOld = sens;
    motor(vel + upr, vel - upr);
  }
  povorot();
}
