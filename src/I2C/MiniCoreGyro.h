#define CORE_GYRO_DEVADDR 		0x10	//location 0x20 shifted to the right 1 bit

#define CORE_GYRO_REG_HEADING		0x04
#define CORE_GYRO_REG_INT_Z		0x06
#define CORE_GYRO_REG_X 		0x08
#define CORE_GYRO_REG_Y 		0x0A
#define CORE_GYRO_REG_Z			0xC
#define CORE_GYRO_REG_OFF_Z	0x0E
#define CORE_GYRO_REG_COE_Z	0x10

//functions
#define CORE_GYRO_RESET			0x4E

#include <Wire.h>
#include <Arduino.h>

#include "MiniCore.h"

class MiniCoreGyro : public MiniCore{
private:

public:
	void begin();		// Constructor
	void begin(int);
	void getDegree(int&);
	byte* getRawX();
	byte* getRawY();
	byte* getRawZ();
	void getRawXYZ(int&,int&,int&);
	void resetGyro();
	void resetScale(float);
};
