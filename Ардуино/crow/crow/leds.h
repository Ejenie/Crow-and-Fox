#include <FastLED.h>
#include <DFRobotDFPlayerMini.h>

const int countLeds = 8;
CRGB eyesLeds[countLeds];

int valOnModule(int val, int mod) {
  return (val + mod) % mod;
}

void permanentLeds(int pinLEDEye, unsigned int color) {
  for (int i = 0; i < countLeds; ++i) {
    eyesLeds[i] = color;
  }
  FastLED.show();
}

void changeLeds(int pinLEDEye, unsigned int color, int countOnLeds, int timePause) {
  for (int i = 0; i < countLeds; ++i) {
    eyesLeds[i] = color;
    eyesLeds[valOnModule(i-countOnLeds, countLeds)] = 0;
    FastLED.show();
    delay(timePause);
  }
}