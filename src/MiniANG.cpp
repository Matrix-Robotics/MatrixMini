#include "MiniANG.h"

void MiniANG::begin(int ver, int ch){

	switch (ch){
    case 1:
		if(ver == 3){
			pin1 = A2;
			pin2 = 4;
		}
		else{
			pin1 = A0;
			pin2 = A1;
		}
		break;
	case 2:
		if(ver == 3){
			pin1 = A0;
			pin2 = A1;
		}
		else{
			pin1 = A1;
			pin2 = A2;
		}
		break;
	case 3:
		if(ver == 3){
			pin1 = A6;
			pin2 = A7;
		}
		else{
			pin1 = A2;
			pin2 = A3;
		}
		break;
	}
}

uint16_t MiniANG::getANG() {
	return analogRead(pin1);
}

bool MiniANG::getDIG() {
	pinMode(pin2, INPUT);
	return digitalRead(pin2);
}
