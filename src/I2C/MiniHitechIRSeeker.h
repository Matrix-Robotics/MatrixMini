// Made by Alex Tkachenko

#define HT_IRSEEKER_DEVADDR 		0x04

#define HT_IRSEEKER_REG_COMMAND	0x41
#define HT_IRSEEKER_REG_DIRECTION		0x42


#include <Wire.h>
#include <Arduino.h>

#include "MiniHitech.h"

class MiniHitechIRSeeker : public MiniHitech{
private:

public:
	void begin();		// Constructor

	byte getDirection();
	byte* getStrength();
	void getStrength(byte &d1,byte &d2,byte &d3,byte &d4,byte &d5);
};
