#define pinServoEyeLeft 13
#define pinServoEyeRight 35
#define pinServoWingPlaneLeft 9
#define pinServoWingPlaneRight 46
#define pinServoWingTurnRight 6
#define pinServoWingTurnLeft 5
#define pinServoStrela 48
#define pinServohead 8
#define pinServoOpening 7

Motors motorA = Motors(11, 49, 43, 3, 41);  //pinPWM, pinA, pinB, interruptNumber, directionPin

DFRobotDFPlayerMini playerCrow;

bool flagBegin = true, kar = false, flagTemp = true;
float kp = 1, kd = 1.6, u = 0, kS = 0.96;
int pos = 0, pos_old = 0, err_old = 0, vel = 20, err = 0, countFox = 0;

uint32_t timerWait = millis(), timerFox = millis();
