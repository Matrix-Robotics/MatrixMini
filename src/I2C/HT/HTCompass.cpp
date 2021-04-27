#include "HTCompass.h"

/**
  * Calibration needs user to hold the device to turn 360 degrees.
  * It is not using. Maybe it will be useful in the future.
  */

// void HTCompass::startCal(){
// 	i2cMUXSelect(_ch, _ver);
// 	i2cWriteData(HT_COMPASS_ADDR, HT_COMPASS_MODE, 0x43);
// }

// bool HTCompass::finishCal(){
// 	i2cMUXSelect(_ch, _ver);
// 	i2cWriteData(HT_COMPASS_ADDR, HT_COMPASS_MODE, 0);
// 	delay(5);

// 	if (i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_MODE, 1) == 2){
// 		return false;
// 	}
// 	else {
// 		return true;
// 	}
// }

//  Get Heading Function returns a number from 0 to 359
uint16_t HTCompass::getHeading(){
	i2cMUXSelect(_ch, _ver);
	return (i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_TWO_DEGREE_HEAD, 1)*2 +
	 		i2cReadData(HT_COMPASS_ADDR, HT_COMPASS_ONE_DEGREE_ADDR, 1));
}
