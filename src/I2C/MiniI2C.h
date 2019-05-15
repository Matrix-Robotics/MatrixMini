#ifndef MiniI2C_H
#define MiniI2C_H

// Made by Alex Tkachenko

//
// This is base class for all I2C sensors
//

#include <Wire.h>
#include <Arduino.h>

class MiniI2C{
protected:
	byte dataBuf[8];

	byte DEVICE_ADDRESS;

	void i2cWriteData(byte addr, byte data);
	void i2cWriteData(byte addr, byte numBytes, byte* data);


	// Reads from I2C and writes to the dataBuf
	byte i2cReadData(byte addr);
	void i2cReadData(byte addr, byte numBytes);

public:
	void begin();		// Constructor
};

#endif
