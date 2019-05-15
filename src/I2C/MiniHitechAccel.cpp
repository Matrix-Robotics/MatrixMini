// Made by Alex Tkachenko

#include "MiniHitechAccel.h"

	//
	// Constructor
	//
	void MiniHitechAccel::begin(){
		DEVICE_ADDRESS = HT_ACCEL_DEVADDR;
	}

	//
	// Get X Value
	//
	int MiniHitechAccel::getX(){
		int tmp =((int)i2cReadData(HT_ACCEL_X8)) << 8;
		tmp += i2cReadData(HT_ACCEL_X2);
		return tmp;
	}

	//
	// Get Y Value
	//
	int MiniHitechAccel::getY(){
		int tmp =((int)i2cReadData(HT_ACCEL_Y8)) << 8;
		tmp += i2cReadData(HT_ACCEL_Y2);
		return tmp;
	}

	//
	// Get Z Value
	//
	int MiniHitechAccel::getZ(){
		int tmp =((int)i2cReadData(HT_ACCEL_Z8)) << 8;
		tmp += i2cReadData(HT_ACCEL_Z2);
		return tmp;
	}

	//
	// Get XYZ Value
	//
	void MiniHitechAccel::getXYZ(int &x, int &y, int &z){
		i2cReadData(HT_ACCEL_X8, 6);
		//Ning Edited @ 01/02/2019
		/*
		x = (((int)dataBuf[0]) << 8) + dataBuf[3];
		y = (((int)dataBuf[1]) << 8) + dataBuf[4];
		z = (((int)dataBuf[2]) << 8) + dataBuf[5];*/
		x = (dataBuf[0] > 127) ? (dataBuf[0] - 256 ) * 4 + dataBuf[3] : dataBuf[0] * 4 + dataBuf[3];
		y = (dataBuf[1] > 127) ? (dataBuf[1] - 256 ) * 4 + dataBuf[4] : dataBuf[1] * 4 + dataBuf[4];
		z = (dataBuf[2] > 127) ? (dataBuf[2] - 256 ) * 4 + dataBuf[5] : dataBuf[2] * 4 + dataBuf[5];
		return;
	}
