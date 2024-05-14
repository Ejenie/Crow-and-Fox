void enc() {
  if (digitalRead(41))
    value--;
  else
    value++;
}
