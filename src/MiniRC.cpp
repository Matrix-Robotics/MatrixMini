#include "MiniRC.h"

/******************************************
               Servos
******************************************/

/**************************************************************************/
/*!
    @brief  Create a Servo object, un-initialized!
    You should never call this, instead have the {@link MatrixMini}
    give you a Servo object with {@link MatrixMini.getServo}
*/
/**************************************************************************/

void MiniRC::begin(int ver, int pin){
  _pin = pin;
  _ver = ver;
  
  if (_ver == 2){
    _RCServo.attach(_pin);
  }
}

void MiniRC::set(int angle) {
  if (_ver == 2){
    _RCServo.write(angle);
  }
  else{
    setPWM_PCA9685(_pin, map(angle, 0, 180, 105, 515));
  }
}