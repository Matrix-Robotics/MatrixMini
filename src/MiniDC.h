#include "utility/MINI_PWMServoDriver.h"
#include <inttypes.h>
#include <Wire.h>

#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4



/** Object that controls and keeps state for a single DC motor */
class MiniDC{
public:
	uint8_t PWMpin, IN1pin, IN2pin;
	MINI_PWMServoDriver * pwm;
	
	MiniDC(void);
	void begin(MINI_PWMServoDriver *, uint8_t, uint8_t, uint8_t);
	void setMode(uint8_t);
	void setSpeed(uint8_t);
	void set(int);
};