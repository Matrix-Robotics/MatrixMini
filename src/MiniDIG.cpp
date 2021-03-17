#include "MiniDIG.h"

void MiniDIG::begin(int pin1, int pin2){
	_pin1 = pin1;
	_pin2 = pin2;

	US.echo = pin2;
	US.trig = pin1;
	// BT  (pin1 , pin2 )= SoftwareSerial (pin1 = _pin2, pin2 = _pin1);
	mode = INPUT;
	
	pinMode(_pin1, mode);
	pinMode(_pin2, mode);
}

bool MiniDIG::get() {
	updateMode(INPUT);
	return digitalRead(_pin1);
}

void MiniDIG::set(byte v) {
	updateMode(OUTPUT);
	digitalWrite(_pin1, v);
}

void MiniDIG::updateMode(int m) {
	if(mode!=m){
		mode = m;
		pinMode(_pin1, mode);
	}
}

// void MiniDIG::BTbegin(){
// 	BT = SoftwareSerial (_pin2, _pin1);
// 	BT.begin(9600);
// }

// bool MiniDIG::BTavailable(){
// 	return BT.available();
// }

// void MiniDIG::BTreadBytes(byte* _bf, byte _num){
// 	BT.readBytes(_bf, _num);
// }