// Made by Alex Tkachenko

#ifndef MiniCore_H
#define MiniCore_H

#define CORE_REG_VERSION		0x00	// 1 char
#define CORE_REG_MANUFACTURER	0x01	// 1 char
#define CORE_REG_ID				0x02	// 1 char

#define CORE_REG_COMMAND		0x03


#include <Wire.h>
#include <Arduino.h>

#include "MiniI2C.h"


class MiniCore : public MiniI2C{
protected:

public:
	void begin();		// Constructor
	byte getVersion();
	char getManufacturer();
	byte getID();
};


#endif
