
#include "MatrixMini.h"



void MatrixMini_::begin(float vbat) {
  Wire.begin();
  det_version();
  init();
  set_VBAT(vbat);
  cli();

    TCCR2B = 3;
    // set prescaler to 32 and starts PWM

    TIMSK2 = 2;
    //Set interrupt on compare match

  sei();
}

void MatrixMini_:: det_version() {

  pinMode(det_pin, INPUT);

  if(digitalRead(det_pin))
  {
    _ver = 2;
  }
  else if (v3_check() == 0x85)
  {
    _ver = 3;
  }
  else
  {
    _ver = 1;
  }

  i2cMUXDisable();

}

void MatrixMini_:: init() {

  switch (_ver){
    case 1:
      
      BTN1.begin(_ver, 8);
      BTN2.begin(_ver, 7);

      D1.begin(2,3); 
      D2.begin(3,4);
      D3.begin(4,5); 
      D4.begin(5,6); 

      init_PCA9685(0x79); //50Hz

      RC1.begin(_ver, 6);
      RC2.begin(_ver, 7);
      RC3.begin(_ver, 8);
      RC4.begin(_ver, 9);

      M1.begin(0);
      M2.begin(5);
      
      RGB2.begin(11, 10, 12);
      RGB1.begin(14, 13, 15);
      break;

    case 2:

      BTN1.begin(_ver, 8);
      BTN2.begin(_ver, 7);

      D1.begin(2,3); 
      D2.begin(3,4); 
      D3.begin(4,5); 
      D4.begin(5,12); 

      init_PCA9685(0x03); //1526Hz

      RC1.begin(_ver, 6);
      RC2.begin(_ver, 9);
      RC3.begin(_ver, 10);
      RC4.begin(_ver, 11);

      M1.begin(0);
      M2.begin(5);

      RGB2.begin(11, 10, 12);
      RGB1.begin(14, 13, 15);

      break;

    case 3:
      
      BTN1.begin(_ver, 3);
      BTN2.begin(_ver, 2);

      D1.begin(5,6); 
      D2.begin(7,9);
      D3.begin(10,11); 
      D4.begin(12,13); 

      init_PCA9685(0x03); //1526Hz

      RC1.begin(_ver, 16);
      RC2.begin(_ver, 4);
      RC3.begin(_ver, 15);
      RC4.begin(_ver, 14);
      
      pinMode(8, OUTPUT);// enable motor driver
      digitalWrite(8, HIGH);
      
      M1.begin(9);
      M2.begin(11);
    
      RGB2.begin(0, 1, 2);
      RGB1.begin(3, 4, 5);

      break;
  }

  A1.begin(_ver, 1);
  A2.begin(_ver, 2);
  A3.begin(_ver, 3);

  I2C1.begin(_ver, 0);
  I2C2.begin(_ver, 1);
  I2C3.begin(_ver, 2);
  I2C4.begin(_ver, 3);

  ENCO.begin(_ver);
}


int MatrixMini_:: v3_check() {
  i2cWriteData(ADDR_ADS1015, ADS1015_Config, 0x05, 0x83);
  delay(100);
  return i2cReadData(ADDR_ADS1015, ADS1015_Config, 1);
}

MatrixMini_ Mini;
