#include "MiniUS.h"

void MiniUS::begin(int e, int t){
	echo = e;
	trig = t;
}

int MiniUS::get(){
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	
	digitalWrite(trig, LOW);
	delayMicroseconds(2);
	
	digitalWrite(trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig, LOW);
	
	int duration = pulseIn(echo, HIGH);
	int distance = 0.017*duration;
	
	distance = constrain(distance, 0, 255);
	return distance;
}