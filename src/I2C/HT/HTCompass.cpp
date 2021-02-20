#include "HTCompass.h"

void HTCompass::startCalibration(){
	i2cWriteData(HT_COMPASS_ADDR, HT_COMPASS_REG_COMMAND, 0x43);
}

bool HTCompass::finishCalibration(){
	i2cWriteData(HT_COMPASS_ADDR, HT_COMPASS_REG_COMMAND, 0);
	delay(50);
	if (i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_REG_COMMAND)){
		return false;
	}
	else {
		return true;
	}
}

uint8_t HTCompass::getHeading2(){
	return i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_HEADING2, 1);
}

uint16_t HTCompass::getHeading1(){
	return getHeading2()*256 + i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_HEADING1, 1);
}

uint16_t HTCompass::getHeading(){
	return i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_HEADING, 1);
}
