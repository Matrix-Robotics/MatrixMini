#include "HT_Color.h"



class MiniI2C{
private:
	void begin(int ver, byte ch);
public:
	friend class MatrixMini_;
	HT_Color HTC;
};

