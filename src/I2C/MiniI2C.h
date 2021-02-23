#ifndef _MINII2C_H_
#define _MINII2C_H_

#include "HT/HTColor.h"
#include "HT/HTCompass.h"

#include "PIXY/PixyCam.h"

class MiniI2C{
private:
	void begin(uint8_t ver, uint8_t ch);

public:
	friend class MatrixMini_;
	HTColor HTColor;
	HTCompass HTCompass;
	PIXY PIXY;
};

#endif
