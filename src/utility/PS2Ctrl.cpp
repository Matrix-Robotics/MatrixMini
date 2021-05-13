#include "PS2Ctrl.h"

void PS2Ctrl::begin(uint8_t sck, uint8_t mosi, uint8_t miso, uint8_t css){
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
	// digitalWrite(_mosi, 1);
	*_mosi_port |= _mosi_mask;
	// digitalWrite(_sck, 1);
	*_sck_port |= _sck_mask;
	// digitalWrite(_css, 0);
	*_css_port &= ~_css_mask;
}

void PS2Ctrl::SWSPI_END(){
	// digitalWrite(_mosi, 1);
	*_mosi_port |= _mosi_mask;
	// digitalWrite(_css, 1);
	*_css_port |= _css_mask;
	_delay_ms(1);
}

void PS2Ctrl::init_PS2(){
	uint8_t chk_ana = 0;

	while(chk_ana != 0x73){
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
		chk_ana = SWSPI_TXRX(0x42);            // the 2nd byte to be returned from the controller should = 0x73 for "red" analouge controller.
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);
		SWSPI_TXRX(0x00);

		SWSPI_END();
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



