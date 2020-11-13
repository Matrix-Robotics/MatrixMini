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
  if(_mode){
    setPWM_PCA9633(_pin+1, 0);
    setPWM_PCA9633(_pin, _speed);
  }
  else{
    setPWM_PCA9633(_pin, 0);
    setPWM_PCA9633(_pin+1, _speed);
  }
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


