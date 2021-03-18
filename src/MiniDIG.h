#ifndef _MiniDIG_h_
#define _MiniDIG_h_

#include <Arduino.h>
#include "utility/HC04.h"
#include <SoftwareSerial.h>


class MiniDIG{
private:
	int _pin1;
	int _pin2;
	int mode;
	void updateMode(int);
	void begin(int, int);
	void softwareserial(int, int);

public:
 	MiniUS US;
	// 99, 98 are impossible values, 
	// for avoiding default definition would be ill-formed.
	// SoftwareSerial BT = SoftwareSerial(13, 12);
	SoftwareSerial BT = SoftwareSerial(99, 94);

 	bool get();
	void set(byte);

	friend class MatrixMini_;
	
};

#endif
