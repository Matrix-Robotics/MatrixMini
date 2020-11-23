// Made by Alex Tkachenko, Frason

#include "Matrix_Color.h"

void M_Color::init(){
	i2cMUXSelect(_ch, _ver);
	i2cWriteData(ADDR_VEML6040, M_COLOR_COMMAND, 0x40);
}

uint16_t M_Color::get(byte color){
	i2cMUXSelect(_ch, _ver);
	return i2cReadData(ADDR_VEML6040, color, 2);
}