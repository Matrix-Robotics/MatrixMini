/*------------------------------------------------------------------------------------------/
-------------------------------------------------------------------------------------------*/
#include "Wire.h"

String old_addr, new_addr;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Type in the Current Arduino Address  ");
  while(!Serial.available());
  old_addr = Serial.readString();
  Serial.println(old_addr);
  int old_addrx = strtol(&old_addr[0],NULL, 16);
  Serial.print("Type in the New Arduino Address      ");
  while(!Serial.available());
  new_addr = Serial.readString();
  Serial.println(new_addr);
  int new_addrx = strtol(&new_addr[0], NULL, 16);
  coreChangeI2C(old_addrx, new_addrx);
}

void coreChangeI2C(int old_address, int new_address){
  if(new_address > 0x0A && new_address <= 0x77 && old_address != 0x0A){
    Wire.beginTransmission(old_address);
    Wire.write(0x70);
    Wire.write(new_address<<1);
    Wire.write(0x55);
    Wire.write(0xAA);
    Wire.endTransmission();
  }
}
