

#define ADDR_VEML6040 	0x10

#define M_COLOR_COMMAND	0x00


#include "../utility/PCA954X.h"


class M_Color{
	private:
		byte _ch;
		int _ver;
		void init();
	public:
		uint16_t get(byte color);
		friend class MiniI2C;
};
