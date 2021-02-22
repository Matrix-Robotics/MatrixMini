#ifndef _MiniDIG_h_
#define _MiniDIG_h_

#include <Arduino.h>
#include "utility/HC04.h"

class MiniDIG{
private:
	int _pin1;
	int _pin2;
	int mode;
	void updateMode(int);
	void begin(int, int);
	
public:
 	MiniUS US;
 	bool get();
	void set(byte);
	friend class MatrixMini_;
};

#endif
