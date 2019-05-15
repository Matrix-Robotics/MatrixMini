// Made by Alex Tkachenko

//
// This is base class for all Hitechnic I2C sensors
//

#ifndef MiniHitech_H
#define MiniHitech_H

#define HT_REG_VERSION		0x00	// 8 chars
#define HT_REG_MANUFACTURER	0x08	// 8 chars
#define HT_REG_TYPE			0x10	// 8 chars


#include <Wire.h>
#include <Arduino.h>
#include "MiniI2C.h"

class MiniHitech: public MiniI2C{
protected:

public:
	void begin();		// Constructor
	char* getVersion();
	char* getManufacturer();
	char* getType();
	char* getAddr();
};



#endif
