#include "PS2Ctrl.h"

bool PS2Ctrl::begin(){
	uint8_t sck, mosi, miso, css;
	if(_ver > 2){
		miso = 5;
		mosi = 6;
		css = 10;
		sck = 11; 
	}
	else{
		miso = 2;
		mosi = 3;
		css = 4;
		sck = 5; 
	}

	_sck_port = portOutputRegister(digitalPinToPort(sck));
	_sck_mask = digitalPinToBitMask(sck);
	
	_mosi_port = portOutputRegister(digitalPinToPort(mosi));
	_mosi_mask = digitalPinToBitMask(mosi);

	_miso_port = portInputRegister(digitalPinToPort(miso));
	_miso_mask = digitalPinToBitMask(miso);
	
	_css_port = portOutputRegister(digitalPinToPort(css));
	_css_mask = digitalPinToBitMask(css);

	pinMode(sck, OUTPUT);
    pinMode(mosi, OUTPUT);
	pinMode(miso, INPUT);
	pinMode(css, OUTPUT);
	if(init_PS2()){
		return true;
	}
	else{
		return false;
	}
	
}

uint8_t PS2Ctrl::SWSPI_TXRX(uint8_t command){
    _delay_us(1);                                         
    uint8_t rx_data = 0x00; 

    for(int i=0;i<8;i++){      
        if(command & _BV(i)){ 
			*_mosi_port |= _mosi_mask; // set mosi to 1
        }
        else{ 
            *_mosi_port &= ~_mosi_mask; // set mosi to 0
        }
		*_sck_port &= ~_sck_mask; // set sck to 0
        _delay_us(1); // wait for output to stabilise

        if(*_miso_port & _miso_mask){ // read _miso pin and store
            bitSet(rx_data,i);
        }
        *_sck_port |= _sck_mask;  // set sck to 1
    }

    *_mosi_port |= _mosi_mask; // set mosi to 1     
    _delay_us(20); // wait for ACK to pass.
	return rx_data;
}

void PS2Ctrl::SWSPI_BEGIN(){
	*_mosi_port |= _mosi_mask;
	*_sck_port |= _sck_mask;
	*_css_port &= ~_css_mask;
}

void PS2Ctrl::SWSPI_END(){
	*_mosi_port |= _mosi_mask;
	*_css_port |= _css_mask;
	_delay_ms(1);
}

bool PS2Ctrl::init_PS2(){
	uint8_t check = 0;
	long tNow = millis();
	while((check != 0x73) && ((millis()-tNow) < 5000)){
		// put controller in config mode
		SWSPI_BEGIN();

		SWSPI_TXRX(0x01);
		SWSPI_TXRX(0x43);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x01);
		SWSPI_TXRX(0x00);

		SWSPI_END();

		// put controller in analouge mode
		SWSPI_BEGIN();

		SWSPI_TXRX(0x01);
		SWSPI_TXRX(0x44);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x01);
		SWSPI_TXRX(0x03);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);

		SWSPI_END();

		// exit config mode
		SWSPI_BEGIN();

		SWSPI_TXRX(0x01);
		SWSPI_TXRX(0x43);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x5A);
		SWSPI_TXRX(0x5A);
		SWSPI_TXRX(0x5A);
		SWSPI_TXRX(0x5A);
		SWSPI_TXRX(0x5A);

		SWSPI_END();

		// poll controller and check in analouge mode.
		SWSPI_BEGIN();

		SWSPI_TXRX(0x01);
		check = SWSPI_TXRX(0x42);  // the 2nd byte should = 0x73 for "red" analouge controller.
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);

		SWSPI_END();
   }
   if(check == 0x73){
	   return true;
   }
   else{
	    return false;
   }

}

void PS2Ctrl::polling(){
	SWSPI_BEGIN();

	SWSPI_TXRX(0x01);
	SWSPI_TXRX(0x42);
	SWSPI_TXRX(0x00);

	_rx[0] = SWSPI_TXRX(0x00);
	_rx[1] = SWSPI_TXRX(0x00);
	_rx[2] = SWSPI_TXRX(0x00);
	_rx[3] = SWSPI_TXRX(0x00);
	_rx[4] = SWSPI_TXRX(0x00);
	_rx[5] = SWSPI_TXRX(0x00);

	SWSPI_END();

	SELECT = 	!(_rx[0]&0x01);
	L3 = 		!(_rx[0]&0x02);
	R3 = 		!(_rx[0]&0x04);
	START = 	!(_rx[0]&0x08);
	UP = 		!(_rx[0]&0x10);
	RIGHT = 	!(_rx[0]&0x20);
	DOWN = 		!(_rx[0]&0x40);
	LEFT = 		!(_rx[0]&0x80);

	L2 = 		!(_rx[1]&0x01);
	R2 = 		!(_rx[1]&0x02);
	L1 = 		!(_rx[1]&0x04);
	R1 = 		!(_rx[1]&0x08);
	TRIANGLE = 	!(_rx[1]&0x10);
	CIRCLE = 	!(_rx[1]&0x20);
	X = 		!(_rx[1]&0x40);
	SQUARE = 	!(_rx[1]&0x80);

	RX = _rx[2];
	RY = _rx[3];
	LX = _rx[4];
	LY = _rx[5];
}



