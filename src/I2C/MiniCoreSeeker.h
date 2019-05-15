// Made by Alex Tkachenko

#define CORE_SEEKERV3_DEVADDR 0x1C	//location 0x38 shifted to the right 1 bit

#define CORE_SEEKERV3_REG_DIR			0x04
#define CORE_SEEKERV3_REG_SIG			0x05
#define CORE_SEEKERV3_REG_DIR600		0x06
#define CORE_SEEKERV3_REG_SIG600		0x07


#include <Wire.h>
#include <Arduino.h>

#include "MiniCore.h"

class MiniCoreSeeker : public MiniCore{
private:

public:
	void begin();		// Constructor
	void begin(int);

	int8_t directionData(unsigned int f = 1200);
	byte signalStrength(unsigned int f = 1200);
};
