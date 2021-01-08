#include "MiniLED.h"


/**************************************************************************/
/*!
    @brief  Create a RGB(led) object, un-initialized!
    You should never call this, instead have the {@link MatrixMini}
    give you a RGB object with {@link MatrixMini.getRGB}
*/
/**************************************************************************/
void MiniLED::begin(int ver, uint8_t ch){
  _ch = ch;
  _ver = ver;
}
/**************************************************************************/
/*!
    @brief  Control the RGB pwm frequencies
    @param  speed The 16-bit PWM value, 0 is dark, 4096 is at full density
*/
/**************************************************************************/

void MiniLED::setRGB(uint8_t PWMR, uint8_t PWMG, uint8_t PWMB) {
  _r = PWMR;
  _g = PWMG;
  _b = PWMB;
  showRGB();
}

void MiniLED::setHSV(int H, float S, float V){
  float X, C, m, part;
  int c;
  _r = 0; _g = 0; _b = 0;

  C = V*S;
  part = (float)H/60;
  X = C*(1 - fabs(fmod(part, 2) - 1));
  m = V - C;

  c = floor(part);
  switch(c){
    case 0:
      _r = C;
      _g = X;
      _b = 0;
      break;
    case 1:
      _r = X;
      _g = C;
      _b = 0;
      break;
    case 2:
      _r = 0;
      _g = C;
      _b = X;
      break;
    case 3:
      _r = 0;
      _g = X;
      _b = C;
      break;
    case 4:
      _r = X;
      _g = 0;
      _b = C;
      break;
    case 5:
      _r = C;
      _g = 0;
      _b = X;
      break;
  }
  _r = (_r+m)*255;
  _g = (_g+m)*255;
  _b = (_b+m)*255;

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