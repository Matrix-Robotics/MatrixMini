#ifndef _HTCompass_H_
#define _HTCompass_H_

#include "../../utility/PCA954X.h"

#define HT_COMPASS_ADDR 				0x01

#define HT_COMPASS_MODE					0x41
#define HT_COMPASS_TWO_DEGREE_HEAD		0x42
#define HT_COMPASS_ONE_DEGREE_ADDR		0x43
#define HT_COMPASS_HEADING_L			0x44

class HTCompass{
private:
	uint8_t _ch, _ver;
public:
	friend class MiniI2C;
	// void startCal();
	// bool finishCal();
	uint16_t getHeading();
};

#endif
