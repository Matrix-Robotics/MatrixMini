
#include "MatrixMini.h"

String inputString = "";
int UART_flag = 0;

void MatrixMini_::begin(float vbat, bool _enUART, long buad) {
  Wire.begin();
  det_version();
  init();
  set_VBAT(vbat);

  if(_enUART){
    Serial.begin(buad);
    inputString.reserve(9);
    UART_flag=1;
  }
  cli();

    TCCR2B = 7;
    // set prescaler to 1/64 and starts PWM

    TIMSK2 = 2;
    //Set interrupt on compare match

  sei();
}

void MatrixMini_:: det_version() {

  pinMode(det_pin, INPUT);
  digitalWrite(8, LOW);
  if(digitalRead(det_pin))
  {
    _ver = 2;
  }
  else if (v3_check() == 4)
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

      M1.begin(_ver, 0);
      M2.begin(_ver, 5);
      
      RGB1.begin(_ver, 13);
      RGB2.begin(_ver, 10);
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

      M1.begin(_ver, 0);
      M2.begin(_ver, 5);

      RGB1.begin(_ver, 13);
      RGB2.begin(_ver, 10);

      break;

    case 3:
      
      BTN1.begin(_ver, 3);
      BTN2.begin(_ver, 2);

      D1.begin(5,6); 
      D2.begin(7,9);
      D3.begin(10,11); 
      D4.begin(12,13); 

      init_PCA9685(0x79); //50Hz
      init_PCA9633();

      RC1.begin(_ver, 12);
      RC2.begin(_ver, 11);
      RC3.begin(_ver, 10);
      RC4.begin(_ver, 9);
      
      pinMode(8, OUTPUT);// enable motor driver
      digitalWrite(8, HIGH);

      setPWM_PCA9685(8, 4095);
      
      M1.begin(_ver, 0);
      M2.begin(_ver, 2);
    
      RGB1.begin(_ver, 0);
      RGB2.begin(_ver, 3);

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
  i2cWriteData(ADDR_PCA9633, PCA9633_MODE2, 0x04);
  delay(100);
  return i2cReadData(ADDR_PCA9633, PCA9633_MODE2, 1);
}

void serialEvent() {
  
  while (Serial.available() && UART_flag) {

    char inChar = Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      bool getFlag = (inputString.length() == 7) ? true : false;
      bool setFlag = (inputString.length() == 9) ? true : false;

      if ((inputString.startsWith("MINI")) && (getFlag || setFlag)){
        uint8_t func = strHex2Uint(inputString.charAt(4), inputString.charAt(5));

        if(setFlag){
          uint8_t para = strHex2Uint(inputString.charAt(6), inputString.charAt(7));

          if(para){
            setMini(func, para-1);
          }
        }
        else if(getFlag){
          serialSendBuffer(getMini(func));
          sendEnable();
        }
      }
      inputString = "";
    }
  }
  
}

uint8_t strHex2Uint(char a, char b){
  char str[2];
  str[0] = a;
  str[1] = b;
  return strtol(str, NULL, 16);
}

void setMini(uint8_t _func, uint8_t _para){
  switch (_func)
  {
    case 1:
      if(_para > 127){
        Mini.M1.set(_para-256);
      }
      else{
        Mini.M1.set(_para);
      }
      break;
    case 2:
      if(_para > 127){
        Mini.M2.set(_para-256);
      }
      else{
        Mini.M2.set(_para);
      }
      break;
    case 3:
      Mini.RC1.set(_para);
      break;
    case 4:
      Mini.RC2.set(_para);
      break;
    case 5:
      Mini.RC3.set(_para);
      break;
    case 6:
      Mini.RC4.set(_para);
      break;
    case 7:
      Mini.D1.set(_para);
      break;
    case 8:
      Mini.D2.set(_para);
      break;
    case 9:
      Mini.D3.set(_para);
      break;
    case 10:
      Mini.D4.set(_para);
      break;
    case 11:
      Mini.RGB1.setR(_para);
      break;
    case 12:
      Mini.RGB1.setG(_para);
      break;
    case 13:
      Mini.RGB1.setB(_para);
      break;
    case 14:
      Mini.RGB2.setR(_para);
      break;
    case 15:
      Mini.RGB2.setG(_para);
      break;
    case 16:
      Mini.RGB2.setB(_para);
      break;
    default:
      break;
  }
}

int getMini(uint8_t _func){
  switch (_func)
  {
    case 128:
      return Mini.BTN1.get();
      break;
    case 129:
      return Mini.BTN2.get();
      break;
    case 130:
      return Mini.D1.get();
      break;
    case 131:
      return Mini.D2.get();
      break;
    case 132:
      return Mini.D3.get();
      break;
    case 133:
      return Mini.D4.get();
      break;
    case 134:
      return Mini.A1.get();
      break;
    case 135:
      return Mini.A2.get();
      break;
    case 136:
      return Mini.A3.get();
      break;
    default:
      return -1;
      break;
  }
}


MatrixMini_ Mini;
