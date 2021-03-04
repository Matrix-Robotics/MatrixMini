#ifndef _MatrixController_h_
#define _MatrixController_h_

#include "../../utility/PCA954X.h"

#define MC_ADDR 			0x08

#define MC_REG_STATUS		0x41
#define MC_REG_TIMEOUT		0x42
#define MC_REG_BATTERY		0x43
#define MC_REG_STARTFLAG	0x44

#define MC_REG_SERVO_ENABLE	0x45	
#define MC_REG_SERVO_SPEED	0x46
#define MC_REG_SERVO_TARGET	0x47

#define MC_REG_SERVO_OFFSET 2

#define MC_REG_MOTOR_POS	0x4E	
#define MC_REG_MOTOR_TARGET	0x52	
#define MC_REG_MOTOR_SPEED	0x56
#define MC_REG_MOTOR_MODE	0x57

#define MC_REG_MOTOR_OFFSET	10

#define MODE_BRAKE			1
#define MODE_POSITION		0



class MatrixController{
	private:
		uint8_t _ch, _ver;
		uint8_t _invert1, _invert2, _invert3, _invert4;

		void begin();
		void motorMode(uint8_t motor, uint8_t mode);
		uint32_t motorPosition(uint8_t);

	public:	
		friend class MiniI2C;

		void motorSet(uint8_t motor_ch, uint8_t speed);
		void motorRound(uint8_t motor_ch, float round);
		void motorInvert(uint8_t motor_ch, bool invert);

		void servoSet(uint8_t servo_ch, uint8_t angle);

		float getBattery();

};

#endif
