#define CLK 2
#define DT 40

#define INB 31
#define INA 39
#define PWM 10

int tail_lim = 4500;
int tail_Clos = 10;

int32_t encTail = 0;
int TailCurrentLimit = 0;

int Myabs(int num) {
  if (num < 0)
    num *= -1;
  return num;
}

void motor (int v1) {
  analogWrite(PWM, Myabs(v1));

  if (v1 > 0) {
    digitalWrite(INB, 1);
    digitalWrite(INA, 0);
  }
  if (v1 < 0) {
    digitalWrite(INB, 0);
    digitalWrite(INA, 1);
  }
  if (v1 == 0) {
    digitalWrite(INB, 1);
    digitalWrite(INA, 1);
  }

}

void isrTail() {
  if (digitalRead(DT))
    encTail++;
  else
    encTail--;
}

void tailOpen() {
  while (Myabs(encTail) < tail_lim)
    motor(-30);
  while (Myabs(encTail) > tail_lim)
    motor(130);
  motor(0);
}

void tailClosed() {
  while (Myabs(encTail) > tail_Clos) {
    motor(130);
  }
  while (Myabs(encTail) < tail_Clos) {
    motor(-30);
  }
  motor(0);
}

void colibrate() {
  motor(200);
  delay(130);
  TailCurrentLimit = analogRead(A2);
  if (TailCurrentLimit >= 100) {
    encTail = 0;
    motor(0);
  }
}
