#define CORE_COLOR_DEVADDR 		0x1E		//location 0x3C shifted to the right 1 bit

#define CORE_COLOR_REG_COLOR		0x04
#define CORE_COLOR_REG_RED			0x05
#define CORE_COLOR_REG_GREEN 		0x06
#define CORE_COLOR_REG_BLUE 		0x07
#define CORE_COLOR_REG_INDEX		0x09	//color index number


#define CORE_COLOR_CMD_ACTIVE		0x00
#define CORE_COLOR_CMD_PASSIVE	0x01
#define CORE_COLOR_CMD_50HZ			0x35
#define CORE_COLOR_CMD_60HZ			0x36
#define CORE_COLOR_CMD_BL_CAL		0x42	//Black Level Calibration
#define CORE_COLOR_CMD_WB_CAL		0x43	//White Balance Calibration

#include <Wire.h>
#include <Arduino.h>

#include "MiniCore.h"

class MiniCoreColor : public MiniCore{
private:

public:
	void begin();		// Constructor
	void begin(int);
	byte getColor();
	byte* getRGB();
	void getRGB(byte&,byte&,byte&);
	byte getR();
	byte getG();
	byte getB();
	byte getGrayscale();
	void setActiveMode();
	void setPassiveMode();
	void setWhiteBalance();
	void setBlackLevel();
};
