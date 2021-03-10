#include "HTColor.h"

uint8_t HTColor::getColorNumber(){
	i2cMUXSelect(_ch, _ver);
	return i2cReadData(HT_COLOR_ADDR, HT_COLOR_COLOR, 1);
}

uint8_t HTColor::getR(){
	i2cMUXSelect(_ch, _ver);
	return i2cReadData(HT_COLOR_ADDR, HT_COLOR_RED, 1);
}

uint8_t HTColor::getG(){
	i2cMUXSelect(_ch, _ver);
	return i2cReadData(HT_COLOR_ADDR, HT_COLOR_GREEN, 1);
}

uint8_t HTColor::getB(){
	i2cMUXSelect(_ch, _ver);
	return i2cReadData(HT_COLOR_ADDR, HT_COLOR_BLUE, 1);
}

uint8_t HTColor::getGrayscale(){
	return 0.3*getR() + 0.59*getG() + 0.11*getB();
}
