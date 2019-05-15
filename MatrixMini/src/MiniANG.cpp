#include "MiniANG.h"

void MiniANG::begin(int portInit){
	port = portInit;
}



int MiniANG::get() {
	return analogRead(port);
}



void MiniANG::set(int v) {
	digitalWrite(port, v);
}
