#include "utility/MINI_PWMServoDriver.h"
#include <inttypes.h>
#include <Wire.h>


class MiniRC
{
  public:
    MiniRC(void);
    void begin(MINI_PWMServoDriver *, uint8_t);
    void set(int pos);
  public:
    uint8_t PWMpin;
    MINI_PWMServoDriver * pwm;
};