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
MiniRC::MiniRC(void) {
  pwm = NULL;
  PWMpin = 0;
}

void MiniRC::begin(MINI_PWMServoDriver * _pwm,uint8_t _PWMpin){
  pwm = _pwm;
  PWMpin = _PWMpin;
}


void MiniRC::set(int pos) {
  uint16_t pulse = map(pos, 0, 180, 150, 550);
  pwm->miniSetPWM(PWMpin, pulse);
}


