#include "HTColor.h"

/**
  * @brief Get color number of given rgb.
  * @return options: Black, White, Cyan, Ocean, Blue,
  * Violet, Magenta, Raspberry, Red, Orange, Yellow,
  * Spring Green, Green, Turquoise.  (Total 13 kinds of color)
  */
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

// R, G, B range is 0 ~ 255 (integer).
uint8_t HTColor::getGrayscale(){
	return 0.3*getR() + 0.59*getG() + 0.11*getB();
}
