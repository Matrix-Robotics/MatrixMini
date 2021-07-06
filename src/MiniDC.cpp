#include "MiniDC.h"



void MiniDC::begin(int ver, int pin){
  _ver = ver;
  _pin = pin;
}

// -100 to 100
void MiniDC::set(int speed) {
  if(speed < 0){
    _mode = BACKWARD;
    speed *= -1;
  }
  else{
    _mode = FORWARD;
  }

  if(_ver < 3){
     _speed = map(speed, 0, 100, 0, 4095);
    setMode_PCA9685();
  }
  else{
     _speed = map(speed, 0, 100, 0, 255);
    setMode_PCA9633();
  }
}

void MiniDC::setMode_PCA9633() {
  if(_mode == FORWARD){
    setPWM_PCA9633(_pin, 0, _speed);
  }
  else{
    setPWM_PCA9633(_pin, _speed, 0);
  }
}

void MiniDC::setMode_PCA9685() {
  if(_pin == 5){
    if(_mode == FORWARD){
      setPWM_PCA9685(_pin-2, 4095, 0, _speed); // IN1, IN2, PWM
    }
    else{
      setPWM_PCA9685(_pin-2, 0, 4095, _speed); // IN1, IN2, PWM
    }
  }
  else{
    if(_mode == FORWARD){
      setPWM_PCA9685(_pin, _speed, 0, 4095); // PWM, IN2, IN1
    }
    else{
      setPWM_PCA9685(_pin, _speed, 4095, 0); // PWM, IN2, IN1
    }
  }
}


