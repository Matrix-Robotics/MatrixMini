#ifndef _MiniDIG_h_
#define _MiniDIG_h_

#include <Arduino.h>
#include "utility/HC04.h"
#include "SoftwareSerial.h"

class MiniDIG{
private:
	int _pin1;
	int _pin2;
	int mode;
	void updateMode(int);
	void begin(int, int);
	
public:
 	MiniUS US;
	// SoftwareSerial BT;
 	bool get();
	void set(byte);
	void BTbegin();
	bool BTavailable();
	void BTreadBytes(byte*, byte);
	friend class MatrixMini_;
};
// SoftwareSerial BT(int pin1, int pin2);

#endif
