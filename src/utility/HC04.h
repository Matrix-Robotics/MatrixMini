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
