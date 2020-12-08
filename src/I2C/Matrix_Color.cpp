// Made by Alex Tkachenko, Frason

#include "Matrix_Color.h"

void M_Color::init(){
	i2cMUXSelect(_ch, _ver);
	i2cWriteData(ADDR_VEML6040, M_COLOR_COMMAND, 0x20);
}

uint16_t M_Color::get(byte color){
	i2cMUXSelect(_ch, _ver);
	int i = 0;
  uint16_t datal = 0; 
  uint32_t datah = 0; 
  Wire.beginTransmission(ADDR_VEML6040);
  Wire.write(color);
  Wire.endTransmission(false);
  Wire.requestFrom(ADDR_VEML6040,2);
  while(Wire.available()) 
  {
    if(i){
      datah = Wire.read();
    }
    else{
      datal = Wire.read();
    }
    i++;
  }
  datah = (datah << 8) + datal;
  return datah; 
}