#define CORE_COMPASS_DEVADDR 		0x24	//location 0x24 shifted to the right 1 bit

//The following Register Addresses are all consisted of 2 bytes (lsb/msb)
#define CORE_COMPASS_REG_HEADING		0x04
//Accelerometer Data Value
#define CORE_COMPASS_ACC_X		0x06
#define CORE_COMPASS_ACC_Y 		0x08
#define CORE_COMPASS_ACC_Z 		0x0A
//Accelerometer Offset Value
#define CORE_COMPASS_ACC_OFF_X		0x12
#define CORE_COMPASS_ACC_OFF_Y 		0x14
#define CORE_COMPASS_ACC_OFF_Z 		0x16
//Magnetometer Data Value
#define CORE_COMPASS_MAG_X 		0x0C
#define CORE_COMPASS_MAG_Y 		0x0E
#define CORE_COMPASS_MAG_Z 		0x10
//Magnetometer Offset Value
#define CORE_COMPASS_MAG_OFF_X 		0x18
#define CORE_COMPASS_MAG_OFF_Y 		0x1A
#define CORE_COMPASS_MAG_OFF_Z 		0x1C
//Coefficients
#define CORE_COMPASS_MAG_COE	0x1E		//Magnetometer Tilt Coefficient
#define CORE_COMPASS_MAG_COE_X	0x22	//Magnetometer X Scale Coefficient
#define CORE_COMPASS_ACC_COE_Y	0x24	//Magnetometer Y Scale Coefficient
#define CORE_COMPASS_ACC_COE	0x20		//Accelerometer Scale Coefficient

//Commands
#define CORE_COMPASS_CMD_NORMAL		0x00
#define CORE_COMPASS_CMD_HARDIRON		0x43	//Hard Iron Calibration Mode
#define CORE_COMPASS_CMD_ADJUST		0x47
#define CORE_COMPASS_CMD_TILTUP		0x55
#define CORE_COMPASS_CMD_TILTDOWN		0x44
#define CORE_COMPASS_CMD_NULLX		0x58
#define CORE_COMPASS_CMD_NULLY		0x59
#define CORE_COMPASS_CMD_NULLZ		0x5A

#include <Wire.h>
#include <Arduino.h>

#include "MiniCore.h"

class MiniCoreCompass : public MiniCore{
private:

public:
	void begin();		// Constructor
	void begin(int);
	void getHeading(int&);
	byte* getAccX();
	byte* getAccY();
	byte* getAccZ();
	void getAccXYZ(int&,int&,int&);
	byte* getMagX();
	byte* getMagY();
	byte* getMagZ();
	void getMagXYZ(int&,int&,int&);
	void calHardIron();
	void nullAccX();
	void nullAccY();
	void nullAccZ();
	void tiltUp();
	void tiltDown();
};
