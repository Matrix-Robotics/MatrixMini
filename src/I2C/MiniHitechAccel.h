// Made by Alex Tkachenko

#define HT_ACCEL_DEVADDR 		0x02

#define HT_ACCEL_X8		0x42
#define HT_ACCEL_Y8		0x43
#define HT_ACCEL_Z8		0x44
#define HT_ACCEL_X2		0x45
#define HT_ACCEL_Y2		0x46
#define HT_ACCEL_Z2		0x47


#include <Wire.h>
#include <Arduino.h>

#include "MiniHitech.h"

class MiniHitechAccel : public MiniHitech{
private:

public:
	void begin();		// Constructor

	int getX();
	int getY();
	int getZ();
	void getXYZ(int &x, int &y, int &z);
};
