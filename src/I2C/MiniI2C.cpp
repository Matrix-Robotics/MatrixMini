// Made by Alex Tkachenko

//
// This is base class for all Hitechnic I2C sensors
//

#include "MiniI2C.h"

	void MiniI2C::i2cWriteData(byte addr, byte data){
		Wire.beginTransmission(DEVICE_ADDRESS);
		Wire.write(addr);
		Wire.write(data);
		Wire.endTransmission(1);
	}

	void MiniI2C::i2cWriteData(byte addr, byte numBytes, byte* data){
		int i;
		Wire.beginTransmission(DEVICE_ADDRESS);
		Wire.write(addr);
		for(i=0; i<numBytes; i++){
			Wire.write(data[i]);
		}
		Wire.endTransmission(1); 
	}


	byte MiniI2C::i2cReadData(byte addr){
		Wire.beginTransmission(DEVICE_ADDRESS);
		Wire.write(addr);
		Wire.endTransmission(1);

		delay(1);

		Wire.requestFrom((uint8_t)DEVICE_ADDRESS, (uint8_t)1);

		delay(1);

		if (Wire.available()){
			dataBuf[0] = Wire.read();
		}

		return dataBuf[0];
	}

	void MiniI2C::i2cReadData(byte addr, byte numBytes){
		Wire.beginTransmission(DEVICE_ADDRESS);
		Wire.write(addr);
		Wire.endTransmission(1);

		delay(1);

		Wire.requestFrom((uint8_t)DEVICE_ADDRESS, (uint8_t)numBytes);

		delay(1);

		int i = 0;
		while (Wire.available() && i<numBytes){
			dataBuf[i++] = Wire.read();
		}
	}

	//
	// Constructor
	//
	void MiniI2C::begin(){

	}
