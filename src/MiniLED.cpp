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

void MiniLED::setRGB(byte R, long G, byte B) {
  if (_ver == 3){
    setPWM_PCA9685(_ch, map(R, 0, 255, 0, 4095), map(G, 0, 255, 0, 4095), map(B, 0, 255, 0, 4095));
  }
  else{
    setPWM_PCA9685(_ch, map(G, 0, 255, 0, 4095), map(R, 0, 255, 0, 4095), map(B, 0, 255, 0, 4095));
  }
  

}

void MiniLED::setHSV(int H, float S, float V){
  float X, C, m, r, g, b, part;
  int c;
  r = 0; g = 0; b = 0;

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
  r = (r+m)*255;
  g = (g+m)*255;
  b = (b+m)*255;

  setRGB(r, g, b);
}

void MiniLED::set(byte color) {
  float r, g, b;
  switch(color)  {
    case BLACK:
      r = 0;
      g = 0;
      b = 0;
      break;
    case RED:
      r = 255;
      g = 0;
      b = 0;
      break;
    case ORANGE:
      r = 255;
      g = 125;
      b = 0;
      break;
    case YELLOW:
      r = 255;
      g = 255;
      b = 0;
      break;
    case GREEN:
      r = 0;
      g = 255;
      b = 0;
      break;
    case CYAN:
      r = 0;
      g = 255;
      b = 255;
      break;
    case BLUE:
      r = 0;
      g = 0;
      b = 255;
      break;
    case MAGENTA:
      r = 255;
      g = 0;
      b = 255;
      break;
    case WHITE:
      r = 255;
      g = 255;
      b = 255;
      break;
  }
  setRGB(r, g, b);
}
