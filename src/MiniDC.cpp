#include "MiniDC.h"



void MiniDC::begin(int pin){
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

  _speed = map(speed, 0, 100, 0, 4095);
  setMode_PCA9685();
}

void MiniDC::setMode_PCA9685() {
  
  int A = AIN1;
  int B = AIN2;

  if(_pin){
    A = BIN1;
    B = BIN2;
  }

  if(_mode){
    setPWM_PCA9685(B, 0);
    setPWM_PCA9685(A, 4095);
  }
  else{
    setPWM_PCA9685(A, 0);
    setPWM_PCA9685(B, 4095);
  }

  setPWM_PCA9685(_pin, _speed);
}


