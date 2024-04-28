int32_t value = 0;

void enc() {
  if (digitalRead(48))
    value++;
  else
    value--;
}
