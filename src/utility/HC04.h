#ifndef _HC04_H_
#define _HC04_H_

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
