// Made by Alex Tkachenko

#include "MiniCoreSeeker.h"
	//
	// Constructor
	//
	void MiniCoreSeeker::begin(){
		DEVICE_ADDRESS = CORE_SEEKERV3_DEVADDR;
	}

	void MiniCoreSeeker::begin(int address){
		DEVICE_ADDRESS = address;
	}
	
	//
	//	Get Directional Data, freq 1200 or 600
	//
	int8_t MiniCoreSeeker::directionData(unsigned int f){
		switch(f){
			case 1200: i2cReadData(CORE_SEEKERV3_REG_DIR); break;
			case 600: i2cReadData(CORE_SEEKERV3_REG_DIR600); break;
			default: dataBuf[0] = 255;
		}
		return (int8_t) dataBuf[0];
	}

	//
	//	Get Signal Strength, freq 1200 or 600
	//
	byte MiniCoreSeeker::signalStrength(unsigned int f){
		switch(f){
			case 1200: i2cReadData(CORE_SEEKERV3_REG_SIG); break;
			case 600: i2cReadData(CORE_SEEKERV3_REG_SIG600); break;
			default: dataBuf[0] = 255;
		}
		return dataBuf[0];
	}
