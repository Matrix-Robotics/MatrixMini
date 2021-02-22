#ifndef _HC04_h_
#define _HC04_h_

#include <Arduino.h>

class MiniUS{
private:
	int trig;
	int echo;
	float duration;
	float distance;

public:
	friend class MiniDIG;
	float get();
};

#endif
