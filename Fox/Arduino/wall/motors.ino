void motor(int mL, int mR) {
  digitalWrite(4, (mL < 0));
  if (mL > 255)
    mL = 255;
  analogWrite(5, mL);

  digitalWrite(7, (mR < 0));
  if (mR > 255)
    mR = 255;
  analogWrite(6, mR);
}
