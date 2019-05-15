// Made by Alex Tkachenko

#define HT_MX_DEVADDR 			0x08

#define HT_MX_REG_STATUS		0x41
#define HT_MX_REG_TIMEOUT		0x42
#define HT_MX_REG_BATTERY		0x43
#define HT_MX_REG_STARTFLAG		0x44

#define HT_MX_REG_SERVO_ENABLE	0x45	
#define HT_MX_REG_SERVO_SPEED	0x46
#define HT_MX_REG_SERVO_TARGET	0x47
#define HT_MX_REG_SERVO_OFFSET 	2

#define HT_MX_REG_MOTOR_POS		0x4E	//lword
#define HT_MX_REG_MOTOR_TARGET	0x52	//lword	
#define HT_MX_REG_MOTOR_SPEED	0x56
#define HT_MX_REG_MOTOR_MODE	0x57
#define HT_MX_REG_MOTOR_OFFSET	10

#define MODE_POWER_FLOAT	0
#define MODE_POWER_BRAKE	1
#define MODE_SPEED			2
#define MODE_POSITION		3

#define Servo1 0
#define Servo2 1
#define Servo3 2
#define Servo4 3
#define Motor1	0
#define Motor2	1
#define Motor3	2
#define Motor4	3


#include <Wire.h>
#include <Arduino.h>

#include "MiniHitech.h"

class MiniHitechCtrl : public MiniHitech{

private:
	//byte Battery;	// x0.04 (0~255)
	byte servoEn;
	
	long mPos[4];
	byte mMode[4];
		
	void byteToLong(byte*, long*);
	void longToByte(long, byte*);

public:	
	void begin();	// Constructor
	
	byte getStatus();
	byte getBattery();
	void setTimeout(byte);
	void setStartflag(byte);
	
	void servoEnable(byte, byte);
	void sendServoEnable(byte);
	void servoSpeed(byte, byte);
	void servoTarget(byte, byte);
	
	long motorPosition(byte);
	void motorTarget(byte, long);
	void motorSpeed(byte, byte);
	
	void motorSetup(byte);
	void motorMode(byte, byte);
	void motorInvert(byte, bool);
	void motorReset(byte);
	void motorPending(byte, byte);
	byte motorBusy(byte);
};