#include "MiniANG.h"

void MiniANG::begin(int ver, int ch){
	_ver = ver;

	switch (ch){
    case 1:
		if(_ver == 3){
			pin1 = A6;
			pin2 = A7;
		}
		else{
			pin1 = A0;
			pin2 = A1;
		}
		break;
	case 2:
		if(_ver == 3){
			pin1 = ADS1015_AIN0;
			pin2 = ADS1015_AIN1;
		}
		else{
			pin1 = A1;
			pin2 = A2;
		}
		break;
	case 3:
		if(_ver == 3){
			pin1 = ADS1015_AIN2;
			pin2 = ADS1015_AIN3;
		}
		else{
			pin1 = A2;
			pin2 = A3;
		}
		break;
	}
}



int MiniANG::get() {
	if(_ver < 3 || pin1 == A6){
		return analogRead(pin1);
	}
	else{
		return adc_read(pin1);
	}
	
}
