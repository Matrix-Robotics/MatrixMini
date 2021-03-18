#ifndef _MINIDIG_H_
#define _MINIDIG_H_

#include <Arduino.h>
#include "utility/HC04.h"
#include <SoftwareSerial.h>

class MiniDIG
{
private:
	int _pin1;
	int _pin2;
	int mode;
	void updateMode(int);
	void begin(int, int);

public:
	MiniUS US;
	SoftwareSerial *BT;

	bool get();
	void set(byte);
	void BTBegin(int);

	friend class MatrixMini_;
};

#endif
