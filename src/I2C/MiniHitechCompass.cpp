// Made by Alex Tkachenko

#include "MiniHitechCompass.h"

	//
	// Constructor
	//
	void MiniHitechCompass::begin(){
		DEVICE_ADDRESS = HT_COMPASS_DEVADDR;
	}

	//
	// Get Color Value
	//
	void MiniHitechCompass::startCalibration(){
		i2cWriteData(HT_COMPASS_REG_COMMAND, 0x43);
		return;
	}

	//
	// Get R Value
	//
	bool MiniHitechCompass::finishCalibration(){
		i2cWriteData(HT_COMPASS_REG_COMMAND, 0);
		delay(50);
		i2cReadData(HT_COMPASS_REG_COMMAND);
		if (dataBuf[0]==0) return true;
		else return false;
	}

	//
	// Get G Value
	//
	byte MiniHitechCompass::getHeading2(){
		i2cReadData(HT_COMPASS_HEADING2);
		return dataBuf[0];
	}

	//
	// Get B Value
	//
	int MiniHitechCompass::getHeading1(){
		int tmp = ((int) getHeading2() ) << 8;
		i2cReadData(HT_COMPASS_HEADING1);
		tmp+=dataBuf[0];
		return tmp;
	}

	//
	// Get RGB Value
	//
	int MiniHitechCompass::getHeading(){
		i2cReadData(HT_COMPASS_HEADING, 2);
		return (((int)dataBuf[0]) << 8) + dataBuf[1];
	}
