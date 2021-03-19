#ifndef _MINIANG_H_
#define _MINIANG_H_

#include <Arduino.h>

class MiniANG{
private:
	int pin1;
	int pin2;
	void begin(int, int);

public:
  	uint16_t getANG();
	bool getDIG();
	friend class MatrixMini_;
};

#endif
