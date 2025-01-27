#ifndef _MINII2C_H_
#define _MINII2C_H_

#include <MatrixController.h>

#include <MatrixColorSensor.h>
// #include <MatrixMotionSensor.h>
#include <MatrixLaserSensor.h>

// #include <MatrixMotorExtension.h>
// #include <MatrixServoExtension.h>

#include "HT/HTColor.h"
#include "HT/HTCompass.h"
#include "PIXY/PixyCam.h"

#include "MX/Mini_MXLaserV2.h"
#include "MX/Mini_MXColorV3.h"
#include "MX/Mini_MXGesture.h"


class MiniI2C{
private:
	void begin(uint8_t ver, uint8_t ch);

public:
	friend class MatrixMini_;
	HTColor HTcolor;
	HTCompass HTcompass;
	PIXYCam PIXYcam;

	MatrixController MXctrl;

	MatrixColor MXcolor;
	// MatrixMotion MXmotion;
	MatrixLaser MXlaser;

	// MatrixMotor MXmotor;
	// MatrixServo MXservo;
	
	MatrixLaserV2 MXLaserV2;
	MatrixColorV3 MXColorV3;
	MatrixGesture MXGesture;
};

#endif
