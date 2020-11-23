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
  void setRGB(byte , long , byte );
  void setHSV(int, float, float);
  void set(byte);

  private:
  void begin(uint8_t, uint8_t, uint8_t);
  uint8_t _r, _g, _b;

  friend class MatrixMini_;
  //Adafruit_NeoPixel pixels;
};
