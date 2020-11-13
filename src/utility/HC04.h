#include <Arduino.h>


class MiniUS{
private:
	
	int trig;
	float duration;
	float distance;
	float sum;
	int echo;

public:
	friend class MiniDIG;
    float get();
	float getAverage(int);
	
};
