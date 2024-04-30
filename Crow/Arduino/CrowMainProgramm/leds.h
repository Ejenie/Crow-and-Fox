#include <FastLED.h>
#include <DFRobotDFPlayerMini.h>
const int pinLedEyeRight = 24;
const int pinLedEyeLeft = 25;
const int countLeds = 8;

CRGB ledLeft[countLeds];
CRGB ledRight[countLeds];

int valOnModule(int val, int mod) {
  return (val + mod) % mod;
}

void permanentLeds(int pinLedEye, uint32_t color) {
  for (int i = 0; i < countLeds; ++i) {
    (pinLedEye == pinLedEyeLeft) ? (ledLeft[i] = color) : (ledRight[i] = color);
    FastLED.show();
  }
}

void changeLeds(int pinLedEye, uint32_t color, int countOnLeds, int timePause) {
  for (int i = 0; i < countLeds; ++i) {
    (pinLedEye == pinLedEyeLeft) ? (ledLeft[i] = color) : (ledRight[i] = color);
    (pinLedEye == pinLedEyeLeft) ? (ledLeft[valOnModule(i - countOnLeds, countLeds)] = 0) : (ledRight[valOnModule(i - countOnLeds, countLeds)] = 0);
    FastLED.show();
    delay(timePause);
  }
}
