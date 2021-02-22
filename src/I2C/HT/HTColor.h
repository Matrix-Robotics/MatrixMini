#ifndef _HTColor_h_
#define _HTColor_h_

#include "../../utility/PCA954X.h"

#define HT_COLOR_ADDR 			0x01

#define HT_COLOR_COLOR		0x42
#define HT_COLOR_RED		0x43
#define HT_COLOR_GREEN 		0x44
#define HT_COLOR_BLUE 		0x45

class HTColor{
private:
	uint8_t _ch, _ver;
public:
	friend class MiniI2C;
	uint8_t getColorNumber();
	uint8_t getR();
	uint8_t getG();
	uint8_t getB();
	uint8_t getGrayscale();
};

#endif