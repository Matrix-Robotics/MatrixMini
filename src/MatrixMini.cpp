#include "MatrixMini.h"

String inputString = "";
int UART_flag = 0;

void MatrixMini_::begin(float vbat, bool _enUART, long buad) {
  Wire.begin();
  det_version();
  init();
  set_VBAT(vbat, _ver);

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
      pinMode(5, OUTPUT);

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
      pinMode(5, OUTPUT);

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

      pinMode(12, OUTPUT);

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

  PS2._ver = _ver;
  
  // ENCO.begin(_ver);
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
  char *ptr;
  ptr = (char*)"-9999";

  return strtol(str, &ptr, 16);
}

int _map(uint8_t _para)
{
    if (_para > 127)
    {
        return (_para - 256) * 2.55;
    }
    else
    {
        return _para * 2.55;
    }
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
    case 17:
      Mini.I2C1.MXservo.setAngle(1, _para);
      break;
    case 18:
      Mini.I2C1.MXservo.setAngle(2, _para);
      break;
    case 19:
      Mini.I2C1.MXservo.setAngle(3, _para);
      break;
    case 20:
      Mini.I2C1.MXservo.setAngle(4, _para);
      break;
    case 21:
      Mini.I2C1.MXservo.setAngle(5, _para);
      break;
    case 22:
      Mini.I2C1.MXservo.setAngle(6, _para);
      break;
    case 23:
      Mini.I2C1.MXservo.setAngle(7, _para);
      break;
    case 24:
      Mini.I2C1.MXservo.setAngle(8, _para);
      break;
    case 25:
      Mini.I2C2.MXservo.setAngle(1, _para);
      break;
    case 26:
      Mini.I2C2.MXservo.setAngle(2, _para);
      break;
    case 27:
      Mini.I2C2.MXservo.setAngle(3, _para);
      break;
    case 28:
      Mini.I2C2.MXservo.setAngle(4, _para);
      break;
    case 29:
      Mini.I2C2.MXservo.setAngle(5, _para);
      break;
    case 30:
      Mini.I2C2.MXservo.setAngle(6, _para);
      break;
    case 31:
      Mini.I2C2.MXservo.setAngle(7, _para);
      break;
    case 32:
      Mini.I2C2.MXservo.setAngle(8, _para);
      break;
    case 33:
      Mini.I2C3.MXservo.setAngle(1, _para);
      break;
    case 34:
      Mini.I2C3.MXservo.setAngle(2, _para);
      break;
    case 35:
      Mini.I2C3.MXservo.setAngle(3, _para);
      break;
    case 36:
      Mini.I2C3.MXservo.setAngle(4, _para);
      break;
    case 37:
      Mini.I2C3.MXservo.setAngle(5, _para);
      break;
    case 38:
      Mini.I2C3.MXservo.setAngle(6, _para);
      break;
    case 39:
      Mini.I2C3.MXservo.setAngle(7, _para);
      break;
    case 40:
      Mini.I2C3.MXservo.setAngle(8, _para);
      break;
    case 41:
      Mini.I2C4.MXservo.setAngle(1, _para);
      break;
    case 42:
      Mini.I2C4.MXservo.setAngle(2, _para);
      break;
    case 43:
      Mini.I2C4.MXservo.setAngle(3, _para);
      break;
    case 44:
      Mini.I2C4.MXservo.setAngle(4, _para);
      break;
    case 45:
      Mini.I2C4.MXservo.setAngle(5, _para);
      break;
    case 46:
      Mini.I2C4.MXservo.setAngle(6, _para);
      break;
    case 47:
      Mini.I2C4.MXservo.setAngle(7, _para);
      break;
    case 48:
      Mini.I2C4.MXservo.setAngle(8, _para);
      break;
    case 49:
      Mini.I2C1.MXmotor.setPWM(1, _map(_para));
      break;
    case 50:
      Mini.I2C1.MXmotor.setPWM(2, _map(_para));
      break;
    case 51:
      Mini.I2C1.MXmotor.setPWM(3, _map(_para));
      break;
    case 52:
      Mini.I2C1.MXmotor.setPWM(4, _map(_para));
      break;
    case 53:
      Mini.I2C2.MXmotor.setPWM(1, _map(_para));
      break;
    case 54:
      Mini.I2C2.MXmotor.setPWM(2, _map(_para));
      break;
    case 55:
      Mini.I2C2.MXmotor.setPWM(3, _map(_para));
      break;
    case 56:
      Mini.I2C2.MXmotor.setPWM(4, _map(_para));
      break;
    case 57:
      Mini.I2C3.MXmotor.setPWM(1, _map(_para));
      break;
    case 58:
      Mini.I2C3.MXmotor.setPWM(2, _map(_para));
      break;
    case 59:
      Mini.I2C3.MXmotor.setPWM(3, _map(_para));
      break;
    case 60:
      Mini.I2C3.MXmotor.setPWM(4, _map(_para));
      break;
    case 61:
      Mini.I2C4.MXmotor.setPWM(1, _map(_para));
      break;
    case 62:
      Mini.I2C4.MXmotor.setPWM(2, _map(_para));
      break;
    case 63:
      Mini.I2C4.MXmotor.setPWM(3, _map(_para));
      break;
    case 64:
      Mini.I2C4.MXmotor.setPWM(4, _map(_para));
      break;
    default:
      break;
  }
}

int16_t getMini(uint8_t _func){
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
      return Mini.A1.getANG();
      break;
    case 135:
      return Mini.A2.getANG();
      break;
    case 136:
      return Mini.A3.getANG();
      break;
    case 137:
      return Mini.A1.getDIG();
      break;
    case 138:
      return Mini.A2.getDIG();
      break;
    case 139:
      return Mini.A3.getDIG();
      break;
    case 140:
      return Mini.D1.US.get();
      break;
    case 141:
      return Mini.D2.US.get();
      break;
    case 142:
      return Mini.D3.US.get();
      break;
    case 143:
      return Mini.D4.US.get();
      break;
    case 144:
      return Mini.I2C1.MXcolor.getColor(R);
      break;
    case 145:
      return Mini.I2C1.MXcolor.getColor(G);
      break;
    case 146:
      return Mini.I2C1.MXcolor.getColor(B);
      break;
    case 147:
      return Mini.I2C1.MXcolor.getColor(C);
      break;
    case 148:
      return Mini.I2C1.MXcolor.getColor(M);
      break;
    case 149:
      return Mini.I2C1.MXcolor.getColor(Y);
      break;
    case 150:
      return Mini.I2C1.MXcolor.getColor(K);
      break;
    case 151:
      return Mini.I2C2.MXcolor.getColor(R);
      break;
    case 152:
      return Mini.I2C2.MXcolor.getColor(G);
      break;
    case 153:
      return Mini.I2C2.MXcolor.getColor(B);
      break;

    case 154:
      return Mini.I2C2.MXcolor.getColor(C);
      break;
    case 155:
      return Mini.I2C2.MXcolor.getColor(M);
      break;
    case 156:
      return Mini.I2C2.MXcolor.getColor(Y);
      break;
    case 157:
      return Mini.I2C2.MXcolor.getColor(K);
      break;
    case 158:
      return Mini.I2C3.MXcolor.getColor(R);
      break;
    case 159:
      return Mini.I2C3.MXcolor.getColor(G);
      break;
    case 160:
      return Mini.I2C3.MXcolor.getColor(B);
      break;
    case 161:
      return Mini.I2C3.MXcolor.getColor(C);
      break;
    case 162:
      return Mini.I2C3.MXcolor.getColor(M);
      break;
    case 163:
      return Mini.I2C3.MXcolor.getColor(Y);
      break;
    case 164:
      return Mini.I2C3.MXcolor.getColor(K);
      break;
    case 165:
      return Mini.I2C4.MXcolor.getColor(R);
      break;
    case 166:
      return Mini.I2C4.MXcolor.getColor(G);
      break;
    case 167:
      return Mini.I2C4.MXcolor.getColor(B);
      break;
    case 168:
      return Mini.I2C4.MXcolor.getColor(C);
      break;
    case 169:
      return Mini.I2C4.MXcolor.getColor(M);
      break;
    case 170:
      return Mini.I2C4.MXcolor.getColor(Y);
      break;
    case 171:
      return Mini.I2C4.MXcolor.getColor(K);
      break;
    case 172:
      return Mini.I2C1.MXcolor.getColorNumber();
      break;
    case 173:
      return Mini.I2C2.MXcolor.getColorNumber();
      break;
    case 174:
      return Mini.I2C3.MXcolor.getColorNumber();
      break;
    case 175:
      return Mini.I2C4.MXcolor.getColorNumber();
      break;
    case 176:
      return Mini.I2C1.MXmotion.getAccel(x);
      break;
    case 177:
      return Mini.I2C1.MXmotion.getAccel(y);
      break;
    case 178:
      return Mini.I2C1.MXmotion.getAccel(z);
      break;
    case 179:
      return Mini.I2C2.MXmotion.getAccel(x);
      break;
    case 180:
      return Mini.I2C2.MXmotion.getAccel(y);
      break;
    case 181:
      return Mini.I2C2.MXmotion.getAccel(z);
      break;
    case 182:
      return Mini.I2C3.MXmotion.getAccel(x);
      break;
    case 183:
      return Mini.I2C3.MXmotion.getAccel(y);
      break;
    case 184:
      return Mini.I2C3.MXmotion.getAccel(z);
      break;
    case 185:
      return Mini.I2C4.MXmotion.getAccel(x);
      break;
    case 186:
      return Mini.I2C4.MXmotion.getAccel(y);
      break;
    case 187:
      return Mini.I2C4.MXmotion.getAccel(z);
      break;
    case 188:
      return Mini.I2C1.MXmotion.getRoll();
      break;
    case 189:
      return Mini.I2C2.MXmotion.getRoll();
      break;
    case 190:
      return Mini.I2C3.MXmotion.getRoll();
      break;
    case 191:
      return Mini.I2C4.MXmotion.getRoll();
      break;
    case 192:
      return Mini.I2C1.MXmotion.getYaw();
      break;
    case 193:
      return Mini.I2C2.MXmotion.getYaw();
      break;
    case 194:
      return Mini.I2C3.MXmotion.getYaw();
      break;
    case 195:
      return Mini.I2C4.MXmotion.getYaw();
      break;
    case 196:
      return Mini.I2C1.MXmotion.getPitch();
      break;
    case 197:
      return Mini.I2C2.MXmotion.getPitch();
      break;
    case 198:
      return Mini.I2C3.MXmotion.getPitch();
      break;
    case 199:
      return Mini.I2C4.MXmotion.getPitch();
      break;
    case 200:
      return Mini.I2C1.MXmotion.getGyro(x);
      break;
    case 201:
      return Mini.I2C1.MXmotion.getGyro(y);
      break;
    case 202:
      return Mini.I2C1.MXmotion.getGyro(z);
      break;
    case 203:
      return Mini.I2C2.MXmotion.getGyro(x);
      break;
    case 204:
      return Mini.I2C2.MXmotion.getGyro(y);
      break;
    case 205:
      return Mini.I2C2.MXmotion.getGyro(z);
      break;
    case 206:
      return Mini.I2C3.MXmotion.getGyro(x);
      break;
    case 207:
      return Mini.I2C3.MXmotion.getGyro(y);
      break;
    case 208:
      return Mini.I2C3.MXmotion.getGyro(z);
      break;
    case 209:
      return Mini.I2C4.MXmotion.getGyro(x);
      break;
    case 210:
      return Mini.I2C4.MXmotion.getGyro(y);
      break;
    case 211:
      return Mini.I2C4.MXmotion.getGyro(z);
      break;

    default:
      return -9999;
      break;
  }
}


MatrixMini_ Mini;
