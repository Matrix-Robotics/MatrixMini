#include <Arduino.h>


class MiniUS{
private:
	int echo;
	int trig;
	
public:
    void begin(int, int);
    int get();
};