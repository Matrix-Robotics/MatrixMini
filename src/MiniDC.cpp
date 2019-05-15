#include "MiniDC.h"



/******************************************
               MOTORS
******************************************/

/**************************************************************************/
/*!
    @brief  Create a DCMotor object, un-initialized!
    You should never call this, instead have the {@link MatrixMini}
    give you a DCMotor object with {@link MatrixMini.getMotor}
*/
/**************************************************************************/
MiniDC::MiniDC(void) {
  pwm = NULL;
  PWMpin = IN1pin = IN2pin = 0;
}

void MiniDC::begin(
  MINI_PWMServoDriver * _pwm, 
  uint8_t _PWMpin,
  uint8_t in1, 
  uint8_t in2)
{
  pwm = _pwm;
  PWMpin = _PWMpin;
  IN1pin = in1;
  IN2pin = in2;
}



/**************************************************************************/
/*!
    @brief  Control the DC Motor direction and action
    @param  cmd The action to perform, can be FORWARD, BACKWARD or RELEASE
*/
/**************************************************************************/
void MiniDC::setMode(uint8_t cmd) {

  switch (cmd) {
  case FORWARD:
    pwm->miniSetPin(IN2pin, LOW);  // take low first to avoid 'break'
    pwm->miniSetPin(IN1pin, HIGH);
    break;
  case BACKWARD:
    pwm->miniSetPin(IN1pin, LOW);  // take low first to avoid 'break'
    pwm->miniSetPin(IN2pin, HIGH);
    break;
  case RELEASE:
    pwm->miniSetPin(IN1pin, LOW);
    pwm->miniSetPin(IN2pin, LOW);
    break;
  }

}

/**************************************************************************/
/*!
    @brief  Control the DC Motor speed/throttle
    @param  speed The 8-bit PWM value, 0 is off, 255 is on
*/
/**************************************************************************/
void MiniDC::setSpeed(uint8_t speed) {
  pwm->miniSetPWM(PWMpin, speed*16);
}


// -100 to 100
void MiniDC::set(int speed) {
  speed = map(speed, -100, 100, -255, 255);         // Add FF here!
  setMode(speed>0?FORWARD:(speed<0?BACKWARD:RELEASE));
  speed = constrain(abs(speed), 0, 255);
  setSpeed(speed);
}