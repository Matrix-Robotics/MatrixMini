#ifndef _MiniI2C_h_
#define _MiniI2C_h_


#include "HT/HTColor.h"
#include "HT/HTCompass.h"

class MiniI2C{
private:
	void begin(uint8_t ver, uint8_t ch);
public:
	friend class MatrixMini_;
	HTColor HTColor;
	HTCompass HTCompass;
};

#endif
