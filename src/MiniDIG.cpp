#include "MiniDIG.h"

void MiniDIG::begin(int pin1, int pin2){
	_pin1 = pin1;
	_pin2 = pin2;

	US.echo = pin2;
	US.trig = pin1;
	
	// 初始化 DHT11 傳感器
    MXDHT.begin(pin1);
	
	// 初始化 DS18B20 傳感器
	MXOnewireDT.begin(pin1);
	
	// pinMode(_pin1, INPUT);
	// pinMode(_pin2, INPUT);
	// Serial = SoftwareSerial(pin2, pin1);
}

bool MiniDIG::get() {
	pinMode(_pin1, INPUT);
	return digitalRead(_pin1);
}

void MiniDIG::set(byte v) {
	pinMode(_pin1, OUTPUT);
	digitalWrite(_pin1, v);
}
