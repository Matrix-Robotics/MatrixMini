// #include "MiniCoreGyro.h"

// 	//
// 	// Constructor
// 	//
// 	void MiniCoreGyro::begin(byte chan){
// 		_chan = chan;
// 		i2cMUXSelect(_chan);
// 		DEVICE_ADDRESS = CORE_GYRO_DEVADDR;
// 	}

// 	void MiniCoreGyro::begin(byte chan, int address){
// 		_chan = chan;
// 		i2cMUXSelect(_chan);
// 		DEVICE_ADDRESS = address;
// 	}

// 	//
// 	// Get Degrees from 0 to 359
// 	//
// void MiniCoreGyro::getDegree(int &value){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(CORE_GYRO_REG_HEADING,2);
// 		value = dataBuf[1] << 8 | dataBuf[0];
// 		return;
// 	}

// 	//
// 	// Get Gyro Axis Value
// 	//
// 	byte* MiniCoreGyro::getRawX(){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(CORE_GYRO_REG_X,2);
// 		return dataBuf;
// 	}

// 	byte* MiniCoreGyro::getRawY(){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(CORE_GYRO_REG_Y,2);
// 		return dataBuf;
// 	}

// 	byte* MiniCoreGyro::getRawZ(){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(CORE_GYRO_REG_Z,2);
// 		return dataBuf;
// 	}

// 	void MiniCoreGyro::getRawXYZ(int &x, int &y, int &z){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(CORE_GYRO_REG_X, 6);
// 		x = dataBuf[1] << 8 | dataBuf[0];
// 		y = dataBuf[3] << 8 | dataBuf[2];
// 		z = dataBuf[5] << 8 | dataBuf[4];
// 		return;
// 	}

// 	//
// 	//	Null gyro offset and reset z axis integrator
// 	//
// 	void MiniCoreGyro::resetGyro(){
// 		i2cMUXSelect(_chan);
// 		i2cWriteData(CORE_REG_COMMAND, CORE_GYRO_RESET);
// 		while(i2cReadData(CORE_REG_COMMAND) !=0);
// 		return;
// 	}

// 	void MiniCoreGyro::resetScale(float value){
// 		i2cMUXSelect(_chan);
// 		byte scale[2];
// 		if(value >= 1) {
// 			scale[1] = 1;
// 			value -= 1;
// 		}
// 		else{
// 			scale[1] = 0;
// 		}
// 		scale[0] = byte(value * 256);
// 		i2cWriteData(CORE_GYRO_REG_COE_Z, 2, scale);
// 		resetGyro();
// 	}
