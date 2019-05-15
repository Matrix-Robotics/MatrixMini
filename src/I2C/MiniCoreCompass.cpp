#include "MiniCoreCompass.h"

	//
	// Constructor
	//
	void MiniCoreCompass::begin(){
		DEVICE_ADDRESS = CORE_COMPASS_DEVADDR;
	}

	void MiniCoreCompass::begin(int address){
		DEVICE_ADDRESS = address;
	}

	void MiniCoreCompass::getHeading(int &value){
		i2cReadData(CORE_COMPASS_REG_HEADING,2);
		value = dataBuf[1] << 8 | dataBuf[0];
		return;
	}

	//
	// Get Accelerometer Value (2 bytes)
	//
	byte* MiniCoreCompass::getAccX(){
		i2cReadData(CORE_COMPASS_ACC_X,2);
		return dataBuf;
	}

	byte* MiniCoreCompass::getAccY(){
		i2cReadData(CORE_COMPASS_ACC_Y,2);
		return dataBuf;
	}

	byte* MiniCoreCompass::getAccZ(){
		i2cReadData(CORE_COMPASS_ACC_Z,2);
		return dataBuf;
	}

	void MiniCoreCompass::getAccXYZ(int &x, int &y, int &z){
		i2cReadData(CORE_COMPASS_ACC_X, 6);
		x = dataBuf[0] << 8 | dataBuf[1];
		y = dataBuf[2] << 8 | dataBuf[3];
		z = dataBuf[4] << 8 | dataBuf[5];
		return;
	}

	//
	// Get Magnetometer Value (2 bytes)
	//
	byte* MiniCoreCompass::getMagX(){
		i2cReadData(CORE_COMPASS_MAG_X,2);
		return dataBuf;
	}

	byte* MiniCoreCompass::getMagY(){
		i2cReadData(CORE_COMPASS_MAG_Y,2);
		return dataBuf;
	}

	byte* MiniCoreCompass::getMagZ(){
		i2cReadData(CORE_COMPASS_MAG_Z,2);
		return dataBuf;
	}

	void MiniCoreCompass::getMagXYZ(int &x, int &y, int &z){
		i2cReadData(CORE_COMPASS_MAG_X, 6);
		x = dataBuf[0] << 8 | dataBuf[1];
		y = dataBuf[2] << 8 | dataBuf[3];
		z = dataBuf[4] << 8 | dataBuf[5];
		return;
	}

	//
	// Calibrations
	//
	void MiniCoreCompass::calHardIron(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COMPASS_CMD_HARDIRON);
		delay(5000);
		i2cWriteData(CORE_REG_COMMAND,CORE_COMPASS_CMD_NORMAL);
		while(1){
			if(i2cReadData(CORE_REG_COMMAND) !=CORE_COMPASS_CMD_HARDIRON) break;
		}
	}

	void MiniCoreCompass::nullAccX(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COMPASS_CMD_NULLX);
		return;
	}

	void MiniCoreCompass::nullAccY(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COMPASS_CMD_NULLY);
		return;
	}

	void MiniCoreCompass::nullAccZ(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COMPASS_CMD_NULLZ);
		return;
	}

	//
	//Tilt Calibrations
	//
	void MiniCoreCompass::tiltUp(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COMPASS_CMD_TILTUP);
		while(1){
			if(i2cReadData(CORE_REG_COMMAND) !=CORE_COMPASS_CMD_TILTUP) break;
		}
	}

	void MiniCoreCompass::tiltDown(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COMPASS_CMD_TILTDOWN);
		while(1){
			if(i2cReadData(CORE_REG_COMMAND) !=CORE_COMPASS_CMD_TILTDOWN) break;
		}
	}
