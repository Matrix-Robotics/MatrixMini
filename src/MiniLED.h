#ifndef _MiniLED_h_
#define _MiniLED_h_

#include "utility/PCA9685.h"


class MiniLED
{
  public:
  void setRGB(uint8_t PWMR, uint8_t PWMG, uint8_t PWMB);
  void setR(uint8_t PWM);
  void setG(uint8_t PWM);
  void setB(uint8_t PWM);
  void setHSV(int H, float S, float V);

  private:
  void begin(int ver, uint8_t ch);
  uint8_t _ch, _ver;
  uint8_t _r = 0, _g = 0, _b = 0;
  void showRGB();

  friend class MatrixMini_;
  
};

#endif
