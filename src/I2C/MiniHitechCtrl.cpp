// Made by Alex Tkachenko

#include "MiniHitechCtrl.h"

	void MiniHitechCtrl::byteToLong(byte* bVal, long * lVal){
		byte * ptr;
		int i;	
		ptr = (byte*) lVal;
		for(i=0; i<4; i++){
			*(ptr+i) = bVal[3-i]; 
		}
		return;
	}
	
	void MiniHitechCtrl::longToByte(long lVal, byte* bVal){
		bVal[0] = lVal >> 24;
		bVal[1] = lVal >> 16;
		bVal[2] = lVal >> 8;
		bVal[3] = lVal;	
	}



	void MiniHitechCtrl::begin(){
		DEVICE_ADDRESS = HT_MX_DEVADDR;

		int i;	
		servoEn = 0x00;
		for(i=0; i<4; i++){
			mMode[i] = 0;
			motorReset(i);
		}
	}

	
	//
	// Get Controller Status
	//
	byte MiniHitechCtrl::getStatus(){
		i2cReadData(HT_MX_REG_STATUS);
		return dataBuf[0];
	}
	
	//
	//	Set TimeOut
	//
	void MiniHitechCtrl::setTimeout(byte t){
		i2cWriteData(HT_MX_REG_TIMEOUT, t);
		return;
	}
	
	//
	// Set Starting Flag
	//
	void MiniHitechCtrl::setStartflag(byte st){
		i2cWriteData(HT_MX_REG_STARTFLAG, st);
		return;
	}
	
	//
	// Get Battery Level
	//
	byte MiniHitechCtrl::getBattery(){
		i2cReadData(HT_MX_REG_BATTERY);
		return dataBuf[0];
	}
	
	//
	// Enable chosen Servo
	//
	void MiniHitechCtrl::servoEnable(byte servo, byte en){
		if(en) bitSet(servoEn, servo);
		else bitClear(servoEn, servo);
		sendServoEnable(servoEn);
	}
	
	//
	//	Sen all Servos Enables
	//
	void MiniHitechCtrl::sendServoEnable(byte data){
		i2cWriteData(HT_MX_REG_SERVO_ENABLE, data);
	}
	
	//
	//	Set Speed of the Specified Servo
	//
	void MiniHitechCtrl::servoSpeed(byte servo, byte spd){
		byte addr = HT_MX_REG_SERVO_SPEED + servo * HT_MX_REG_SERVO_OFFSET;
		i2cWriteData(addr, spd);
	}
	
	//
	//	Set Target of the Specified Servo
	//
	void MiniHitechCtrl::servoTarget(byte servo, byte target){
		byte addr = HT_MX_REG_SERVO_TARGET + servo * HT_MX_REG_SERVO_OFFSET;
		i2cWriteData(addr, target);
	}
	
	//
	//	Get DC motor Position (4B)
	//
	long MiniHitechCtrl::motorPosition(byte motor){
		byte addr = HT_MX_REG_MOTOR_POS + motor * HT_MX_REG_MOTOR_OFFSET;
		i2cReadData(addr, 4);
		byteToLong(dataBuf, &mPos[motor]);
		return mPos[motor];
	}
	
	//
	//	Set DC Motor Target
	//
	void MiniHitechCtrl::motorTarget(byte motor, long target){
		longToByte(target, dataBuf);
		byte addr = HT_MX_REG_MOTOR_TARGET + motor * HT_MX_REG_MOTOR_OFFSET;
		i2cWriteData(addr, 4, dataBuf);
		return;
	}

	//
	// Set DC Motor Speed
	//
	void MiniHitechCtrl::motorSpeed(byte motor, byte speed){
		byte addr = HT_MX_REG_MOTOR_SPEED + motor * HT_MX_REG_MOTOR_OFFSET;
		i2cWriteData(addr, speed);
		return;
	}
	
	//
	// Send Setup data to the Motor
	//
	void MiniHitechCtrl::motorSetup(byte motor){
		byte addr = HT_MX_REG_MOTOR_MODE + motor * HT_MX_REG_MOTOR_OFFSET;
		i2cWriteData(addr, mMode[motor]);
		delay(500);
		i2cReadData(addr);
		mMode[motor] = dataBuf[0];
		return;
	}
	
	//
	// Set DC Motor mode
	//
	void MiniHitechCtrl::motorMode(byte motor, byte mode){
		switch(mode){
			case MODE_POWER_FLOAT: 
				bitClear(mMode[motor], 0);
				bitClear(mMode[motor], 1);
				break;
			case MODE_POWER_BRAKE: 
				bitSet(mMode[motor], 0);
				bitClear(mMode[motor], 1);
				break;
			case MODE_SPEED: 
				bitClear(mMode[motor], 0);
				bitSet(mMode[motor], 1);
				break;
			case MODE_POSITION: 
				bitSet(mMode[motor], 0);
				bitSet(mMode[motor], 1);
				break;
		}
		motorSetup(motor);
		return;
	}
	
	//
	// Invert DC
	//
	void MiniHitechCtrl::motorInvert(byte motor, bool invert){
		if(invert) bitSet(mMode[motor], 4);
		else bitClear(mMode[motor], 4);
		motorSetup(motor);
		return;
	}
	
	//
	// Reset DC
	//
	void MiniHitechCtrl::motorReset(byte motor){
		bitSet(mMode[motor], 2);
		motorSetup(motor);
		return;
	}
	
	//
	// Pending DC
	//
	void MiniHitechCtrl::motorPending(byte motor, byte pending){
		if(pending) bitSet(mMode[motor], 3);
		else bitClear(mMode[motor], 3);
		motorSetup(motor);
		return;
	}
	
	