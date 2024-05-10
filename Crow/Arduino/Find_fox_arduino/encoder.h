int32_t value = 0;

void enc() {
  if (digitalRead(41))
    ++value;
  else
    --value;
}
