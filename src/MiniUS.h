#include <Arduino.h>


class MiniUS{
private:
	int echo;
	int trig;
	float duration;
	float distance;
	float sum;

public:
    void begin(int, int);
    float get();
};
