
#include "src/MatrixMini.h"
#include <Arduino.h>
  
void setup(){
  
  Serial.begin(115200);
  
  
  Mini.begin();
  //i2cMUXSelect(0, 2);
}

void loop(){
  //Serial.println(Mini._ver);
  Mini.M1.set(100);
  Mini.M2.set(100);
  Mini.RGB1.setRGB(0,100,0);
  Mini.RGB2.setRGB(0,0,0);
  delay(1000);
  Mini.M1.set(-100);
  Mini.M2.set(-100);
  Mini.RGB2.setRGB(0,100,0);
  Mini.RGB1.setRGB(0,0,0);
  delay(1000);

//  // vccc = Mini.I2C1.HTC.get(RED);
//   //sss(11);
//   //setPWM_PCA9685(11, 4095, 0, 0);
//   Serial.println(Mini._ver);
//   Mini.RGB1.setRGB(0, 0, 100);
//   //Mini.RGB2.setRGB(0, 0, 0);
//   delay(300);
//   //ssss(11);
//   //setPWM_PCA9685(11, 0, 0, 4095);
//   Mini.RGB1.setRGB(0, 0, 0);
//   //Mini.RGB2.setRGB(0, 0, 100);
//   delay(300);
  //vccc = float(analogRead(A3));
  // Mini.RGB1.setRGB(vccc >> 16, vccc >> 8, vccc);
  // Serial.println(Mini.BTN2.get());

  // Serial.println("=================");
  // i2cWriteData(0x22, 0x56);
  // buff= i2cReadData(0x22, 2);
  // Serial.println(buff);
  // Serial.print("L turn: "); Serial.println(Mini.ENCO.get_Turn(L));
  // Serial.print("L angle: "); Serial.println(Mini.ENCO.get_Angle(L));
  // Serial.print("L D: ");   Serial.println(Mini.ENCO.get_Distance(L));
  // Serial.println("");
  // Serial.print("R turn: ");  Serial.println(Mini.ENCO.get_Turn(R));
  // Serial.print("R angle: ");  Serial.println(Mini.ENCO.get_Angle(R));
  // Serial.print("R D: ");  Serial.println(Mini.ENCO.get_Distance(R));
  //delay(500);
 
   
  //Mini.RGB2.setRGB(0, 100, 0);

  

}
void sss(int ch){
  Wire.beginTransmission(ADDR_PCA9685);
    Wire.write(PCA9685_PWM0_ON_L + 4*ch);


    Wire.write(0);
    Wire.write(0);
    Wire.write(4095);
    Wire.write(4095>>8);

    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);

    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);

    Wire.endTransmission();
}

void ssss(int ch){
  Wire.beginTransmission(ADDR_PCA9685);
    Wire.write(PCA9685_PWM0_ON_L + 4*ch);


    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);

    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);

    Wire.write(0);
    Wire.write(0);
    Wire.write(4095);
    Wire.write(4095>>8);

    Wire.endTransmission();
}    