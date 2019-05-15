#include "MiniDIG.h"

void MiniDIG::begin(int portInit){
	port = portInit;
	
	mode = OUTPUT;
	pinMode(port, mode);
}



bool MiniDIG::get() {
	updateMode(INPUT);
	return digitalRead(port);
}



void MiniDIG::set(byte v) {
	updateMode(OUTPUT);
	digitalWrite(port, v);
}



void MiniDIG::updateMode(int m) {
	if(mode!=m){
		mode = m;
		pinMode(port, mode);
	}
}

