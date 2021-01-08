#include "utility/PCA9685.h"


class MiniLED
{
  public:
  void setRGB(uint8_t PWMR, uint8_t PWMG, uint8_t PWMB);
  void setHSV(int H, float S, float V);

  private:
  void begin(int ver, uint8_t ch);
  uint8_t _ch, _ver;
  uint8_t _r, _g, _b;
  void showRGB();

  friend class MatrixMini_;
  
};
