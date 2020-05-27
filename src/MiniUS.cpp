#include "MiniUS.h"

void MiniUS::begin(int e, int t){
	echo = e;
	trig = t;
	sum = 0;
}

float MiniUS::get(){
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	digitalWrite(trig, LOW);
	delayMicroseconds(2);

	digitalWrite(trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig, LOW);

	duration = pulseIn(echo, HIGH);
	distance = 0.017*duration;

	distance = constrain(distance, 4.0, 200.0);
	return distance;
}
