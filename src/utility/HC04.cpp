#include "HC04.h"

float MiniUS::get(){

	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	digitalWrite(trig, LOW);
	delayMicroseconds(2);

	digitalWrite(trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig, LOW);

	duration = pulseIn(echo, HIGH, 26500); //timeout = 450cm

	if (duration == 0){
		delayMicroseconds(100);
		// sensor timeout
		distance = -1;
	}
	else if (duration > 0 && duration < 294){
		distance = 5.0;
	}
	else{
		distance = 0.017 * duration;
	}
	return distance;
}
