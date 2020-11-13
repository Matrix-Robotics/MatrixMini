// Made by Alex Tkachenko, Frason

#include "HT_Color.h"


uint32_t HT_Color::get(byte color){
	i2cMUXSelect(_ch, _ver);
	return i2cReadData(ADDR_HT_Color, color, 3);
}

//
// Get RGB Value
// //
// byte MiniHitechColor::getGrayscale(){
// 	i2cMUXSelect(_chan);
// 	getRGB();
// 	return 0.3*dataBuf[0] + 0.59*dataBuf[1] + 0.11*dataBuf[2];
// }
