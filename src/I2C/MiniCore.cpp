// Made by Alex Tkachenko

//
// This is base class for all Core I2C sensors
//

#include "MiniCore.h"
	//
	// Constructor
	//
	void MiniCore::begin(){

	}

	//
	// Get Version Number
	//
	byte MiniCore::getVersion(){
		i2cReadData(CORE_REG_VERSION);
		return dataBuf[0]; 
	}
	
	//
	// Get Manufacturer Name
	//
	char MiniCore::getManufacturer(){
		i2cReadData(CORE_REG_MANUFACTURER);
		return dataBuf[0]; 
	}
	
	//
	// Get Controller ID
	//
	byte MiniCore::getID(){
		i2cReadData(CORE_REG_ID);
		return dataBuf[0];
	}