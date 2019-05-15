// Made by Alex Tkachenko

#define HT_COLOR_DEVADDR 		0x03

#define HT_COLOR_REG_COMMAND	0x41
#define HT_COLOR_REG_COLOR		0x42
#define HT_COLOR_REG_RED		0x43
#define HT_COLOR_REG_GREEN 		0x44
#define HT_COLOR_REG_BLUE 		0x45


#include <Wire.h>
#include <Arduino.h>

#include "MiniHitech.h"

class MiniHitechColor : public MiniHitech{
private:

public:
	void begin();		// Constructor

	byte getColor();
	byte* getRGB();
	void getRGB(byte&,byte&,byte&);
	byte getR();
	byte getG();
	byte getB();
	byte getGrayscale();
};
