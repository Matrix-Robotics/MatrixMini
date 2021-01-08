#include "utility/PCA9685.h"

#define BLACK 0
#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define CYAN 5
#define BLUE 6
#define MAGENTA 7
#define WHITE 8



class MiniLED
{
  public:
  void setRGB(byte R, byte G, byte B);
  void setHSV(int H, float S, float V);
  void setColor(byte);

  private:
  void begin(int ver, uint8_t ch);
  uint8_t _ch, _ver;
  uint8_t _r, _g, _b;
  void showRGB();

  friend class MatrixMini_;
  //Adafruit_NeoPixel pixels;
};
