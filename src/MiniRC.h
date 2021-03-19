#ifndef _MINIRC_H_
#define _MINIRC_H_

#include "utility/PCA9685.h"
#include <Servo.h>


class MiniRC {
  public:
    void set(int angle);
	  friend class MatrixMini_;

  private:
    int _pin;
    int _ver;
    Servo _RCServo;
    void begin(int, int);
};

#endif
