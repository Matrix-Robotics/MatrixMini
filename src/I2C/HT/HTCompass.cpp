#include "HTCompass.h"

void HTCompass::startCal(){
	i2cWriteData(HT_COMPASS_ADDR, HT_COMPASS_MODE, 0x43);
}

bool HTCompass::finishCal(){
	i2cWriteData(HT_COMPASS_ADDR, HT_COMPASS_MODE, 0);
	delay(5);

	if (i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_MODE, 1) == 2){
		return false;
	}
	else {
		return true;
	}
}

uint16_t HTCompass::getHeading(){
	return (i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_TWO_DEGREE_HEAD, 1)*2 +
	 		i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_ONE_DEGREE_ADDR, 1));
}
