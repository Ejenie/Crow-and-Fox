#define PIN_TRIG 10
#define PIN_ECHO 11

int vel = 50, err, upr;
float kprop = 0.5, kdef = 2.5;
int sens = 0, sensOld = 0;
float k_filtr = 0.3;
uint32_t timerW = millis();

void setup() {
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  while (millis() - timerW < 5000) {
    sens = analogRead(A5);
    Serial.println(sens);
    upr = (sens - 600) * kprop + (sens - sensOld) * kdef;
    motor(vel + upr, vel - upr);
  }
  motor(0, 0);
}
