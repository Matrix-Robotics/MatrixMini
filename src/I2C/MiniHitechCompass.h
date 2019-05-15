// Made by Alex Tkachenko

#define HT_COMPASS_DEVADDR 		0x01

#define HT_COMPASS_REG_COMMAND	0x41
#define HT_COMPASS_HEADING2		0x42
#define HT_COMPASS_HEADING1		0x43
#define HT_COMPASS_HEADING 		0x44


#include <Wire.h>
#include <Arduino.h>

#include "MiniHitech.h"

class MiniHitechCompass : public MiniHitech{
private:

public:
	void begin();		// Constructor

	void startCalibration();
	bool finishCalibration();
	byte getHeading2();
	int getHeading1();
	int getHeading();
};
