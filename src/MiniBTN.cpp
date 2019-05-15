#include "MiniBTN.h"

void MiniBTN::begin(int portInit){
	port = portInit;
	
	pinMode(port, OUTPUT);
	digitalWrite(port, HIGH);
}


bool MiniBTN::get() {
  return !digitalRead(port);
}


