#ifndef _MiniANG_h_
#define _MiniANG_h_

#include <Arduino.h>

class MiniANG{
private:
	int pin1;
	int pin2;
	void begin(int, int);

public:
  	int get();
	friend class MatrixMini_;
};

#endif
