#include "HC04.h"

float MiniUS::get(){

	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	digitalWrite(trig, LOW);
	delayMicroseconds(2);

	digitalWrite(trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig, LOW);

	duration = pulseIn(echo, HIGH, 26500);  //timeout = 450cm
	distance = 0.017*duration;

	return distance;
}

float MiniUS::getAverage(int times){
	sum = 0;
	for(int i = 0; i < times; i++){
		sum += get();
	}
	sum = sum / times;
	return sum;
}
