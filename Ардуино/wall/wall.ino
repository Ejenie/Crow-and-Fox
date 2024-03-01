#define PIN_TRIG 10
#define PIN_ECHO 11

int vel = 100, err, upr;
float kprop = 0.5, kdef = 1;
int sens = 0, sensOld = 0;
float k_filtr = 0.3;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  static int sonarFiltr;
  int sonarRaw = sonar();
  sonarFiltr = sonarRaw * k_filtr + sonarFiltr * (1 - k_filtr);

  sensOld = sens;
  sens = analogRead(A5);
  upr = (sens - 350) * kprop + (sens - sensOld) * kdef;
  motor(vel - upr, vel + upr);
}
