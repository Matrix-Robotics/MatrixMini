#include "PCA954X.h"


void i2cWriteData(uint8_t dev, uint8_t addr){

	Wire.beginTransmission(dev);

	Wire.write(addr);

	Wire.endTransmission(1);
}

void i2cWriteData(uint8_t dev, uint8_t addr, uint8_t data){

	Wire.beginTransmission(dev);

	Wire.write(addr);
	Wire.write(data);

	Wire.endTransmission(1);
}

void i2cWriteData(uint8_t dev, uint8_t addr, uint8_t data, uint8_t data2){

	Wire.beginTransmission(dev);

	Wire.write(addr);
	Wire.write(data);
	Wire.write(data2);

	Wire.endTransmission(1);
}

void i2cWriteBytes(uint8_t dev, uint8_t addr, uint32_t data, uint8_t numBytes){
	uint32_t d;
	int shift;

	Wire.beginTransmission(dev);

	Wire.write(addr);

	for(int i = numBytes-1; i > -1; i--){
		shift = 8*i;
		d = data >> shift;
		Wire.write(d);
		data = data - (d << shift);
	}

	Wire.endTransmission(1);
}

uint32_t i2cReadData(uint8_t dev, uint8_t numBytes){

	Wire.requestFrom(dev, numBytes);

	delay(1);

	uint32_t dataBuf = 0;

	int i = 0;

	while (Wire.available() && i<numBytes){
		dataBuf = dataBuf << 8;
		dataBuf += Wire.read();
		i++;
	}
	return dataBuf;
}

uint32_t i2cReadData(uint8_t dev, uint8_t addr, uint8_t numBytes){
	
	Wire.beginTransmission(dev);
	Wire.write(addr);
	Wire.endTransmission(1);

	delay(1);

	Wire.requestFrom(dev, numBytes);

	delay(1);

	uint32_t dataBuf = 0;

	int i = 0;

	while (Wire.available() && i<numBytes){
		dataBuf = dataBuf << 8;
		dataBuf += Wire.read();
		i++;
	}
	return dataBuf;
}



void i2cMUXSelect(uint8_t channel, int ver){
	switch (ver)
	{
	case 2:
		i2cWriteData(ADDR_PCA954X, channel+4);
		delay(10);
		break;
	case 3:
		i2cWriteData(ADDR_PCA954X, (1 << channel));
		delay(10);
		break;
	default:
		break;
	}
}

void i2cMUXDisable(){
	i2cWriteData(ADDR_PCA954X, 0x00);
	delay(10);
}