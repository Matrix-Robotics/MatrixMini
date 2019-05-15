// Made by Alex Tkachenko

#include "MiniHitechIRSeeker.h"

	//
	// Constructor
	//
	void MiniHitechIRSeeker::begin(){
		DEVICE_ADDRESS = HT_IRSEEKER_DEVADDR;
	}

	//
	// Get DC Direction Value
	//
	byte MiniHitechIRSeeker::getDirection(){
		return i2cReadData(HT_IRSEEKER_REG_DIRECTION);
	}

	//
	// Get IR Strength Value
	//
	byte* MiniHitechIRSeeker::getStrength(){
		i2cReadData(HT_IRSEEKER_REG_DIRECTION, 6);
		return dataBuf;
	}

	//
	// Get IR Strength Value
	//
	void MiniHitechIRSeeker::getStrength(byte &d1, byte &d2, byte &d3, byte &d4, byte &d5){
		i2cReadData(HT_IRSEEKER_REG_DIRECTION, 6);
		d1 = dataBuf[1];
		d2 = dataBuf[2];
		d3 = dataBuf[3];
		d4 = dataBuf[4];
		d5 = dataBuf[5];
		return;
	}
