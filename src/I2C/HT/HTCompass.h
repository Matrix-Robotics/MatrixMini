#ifndef _HTCompass_h_
#define _HTCompass_h_

#include "../../utility/PCA954X.h"

#define HT_COMPASS_ADDR 		0x01

#define HT_COMPASS_REG_COMMAND	0x41
#define HT_COMPASS_HEADING2		0x42
#define HT_COMPASS_HEADING1		0x43
#define HT_COMPASS_HEADING 		0x44

class HTCompass{
private:
	uint8_t _ch, _ver;
public:
	friend class MiniI2C;
	void startCalibration();
	bool finishCalibration();
	uint8_t getHeading2();
	uint16_t getHeading1();
	uint16_t getHeading();
};

#endif