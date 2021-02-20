#include "HT/HTColor.h"
#include "HT/HTCompass.h"

class MiniI2C{
private:
	void begin(int ver, byte ch);
public:
	friend class MatrixMini_;
	HTColor HTColor;
	HTCompass HTCompass;
};

