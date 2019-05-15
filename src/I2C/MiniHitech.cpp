// Made by Alex Tkachenko

//
// This is base class for all Hitechnic I2C sensors
//



#include "MiniHitech.h"

	//
	// Constructor
	//
	void MiniHitech::begin(){

	}

	//
	// Get Version Number
	//
	char* MiniHitech::getVersion(){
		i2cReadData(HT_REG_VERSION, 8);
		dataBuf[7] = '\0';
		return (char*) dataBuf;
	}

	//
	// Get Manufacturer Name
	//
	char* MiniHitech::getManufacturer(){
		i2cReadData(HT_REG_MANUFACTURER, 8);
		dataBuf[7] = '\0';
		return (char*) dataBuf;
	}

	//
	// Get Controller ID
	//
	char* MiniHitech::getType(){
		i2cReadData(HT_REG_TYPE, 8);
		dataBuf[7] = '\0';
		return (char*) dataBuf;
	}

	char* MiniHitech::getAddr(){
		i2cReadData(0x02,3);
		dataBuf[2] = '\0';
		return (char*) dataBuf;
	}
