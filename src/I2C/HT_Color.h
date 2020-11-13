// Made by Alex Tkachenko, Frason

#define ADDR_HT_Color 	0x01

//#define HT_COLOR_COMMAND	0x41
//#define HT_COLOR_COLOR		0x42
#define RED			0x43
#define GREEN 		0x44
#define BLUE 		0x45

#include "../utility/PCA954X.h"


class HT_Color{
	private:
		byte _ch;
		int _ver;
	public:
		uint32_t get(byte color);
		friend class MiniI2C;
};
