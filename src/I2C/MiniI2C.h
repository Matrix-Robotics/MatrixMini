#ifndef _MINII2C_H_
#define _MINII2C_H_

// #include <MatrixColorSensor.h>
// #include <MatrixMotionSensor.h>
// #include <MatrixMotorExtension.h>
// #include <MatrixServoExtension.h>
// #include <MatrixController.h>


#include "HT/HTColor.h"
#include "HT/HTCompass.h"
#include "PIXY/PixyCam.h"
class MiniI2C{
private:
	void begin(uint8_t ver, uint8_t ch);

public:
	friend class MatrixMini_;
	HTColor HTcolor;
	HTCompass HTcompass;
	PIXYCam PIXYcam;
	// MatrixController MXctrl;
	// MatrixColor MXcolor;
	// MatrixMotion MXmotion;
	// MatrixMotor MXmotor;
	// MatrixServo MXservo;
};

#endif
