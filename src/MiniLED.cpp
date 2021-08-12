#include "MiniLED.h"

void MiniLED::begin(int ver, uint8_t ch){
  _ch = ch;
  _ver = ver;
}

void MiniLED::setRGB(uint8_t PWMR, uint8_t PWMG, uint8_t PWMB) {
  _r = PWMR;
  _g = PWMG;
  _b = PWMB;
  showRGB();
}

void MiniLED::setR(uint8_t PWM){
  _r = PWM;

  showRGB();
}

void MiniLED::setG(uint8_t PWM){
  _g = PWM;

  showRGB();
}

void MiniLED::setB(uint8_t PWM){
  _b = PWM;

  showRGB();
}

void MiniLED::setHSV(int H, float S, float V){
  float X, C, m, part, r, g, b;
  int c;

  C = V*S;
  part = (float)H/60;
  X = C*(1 - fabs(fmod(part, 2) - 1));
  m = V - C;

  c = floor(part);
  switch(c){
    case 0:
      r = C;
      g = X;
      b = 0;
      break;
    case 1:
      r = X;
      g = C;
      b = 0;
      break;
    case 2:
      r = 0;
      g = C;
      b = X;
      break;
    case 3:
      r = 0;
      g = X;
      b = C;
      break;
    case 4:
      r = X;
      g = 0;
      b = C;
      break;
    case 5:
      r = C;
      g = 0;
      b = X;
      break;
  }
  _r = (r+m)*255;
  _g = (g+m)*255;
  _b = (b+m)*255;

  showRGB();
}

void MiniLED::showRGB() {
  if (_ver == 3){
    setPWM_PCA9685(_ch, map(_r, 0, 255, 0, 4095), map(_g, 0, 255, 0, 4095), map(_b, 0, 255, 0, 4095));
  }
  else{
    setPWM_PCA9685(_ch, map(_g, 0, 255, 0, 4095), map(_r, 0, 255, 0, 4095), map(_b, 0, 255, 0, 4095));
  }
  
}
