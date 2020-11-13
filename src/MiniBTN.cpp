#include "MiniBTN.h"

void MiniBTN::begin(int ver, int portInit){
	port = portInit;
	pinMode(port, INPUT);
	
	if(ver == 1){
		digitalWrite(port, HIGH);
	}
}


bool MiniBTN::get() {
  return !digitalRead(port);
}
