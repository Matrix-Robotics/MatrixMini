/******************************************************************

 ******************************************************************/

#ifndef _MatrixMini_h_
#define _MatrixMini_h_

#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>

#include "utility/MINI_PWMServoDriver.h"
#include "MiniDC.h"
#include "MiniRC.h"
#include "MiniLED.h"
#include "MiniUS.h"
#include "MiniBTN.h"
#include "MiniDIG.h"
#include "MiniANG.h"
#include "I2C/SensorList.h"



class MatrixMini{
private:
    TwoWire *_i2c;
    uint8_t _addr;
    uint16_t _freq;
    
    // Modules
    MINI_PWMServoDriver _pwm;

public:
    MatrixMini(uint8_t addr = 0x60);
    //void begin(uint16_t freq = 1600);
    void begin(uint16_t freq = 60);

    // Modules
    MiniDC M1, M2;
    MiniRC RC1, RC2, RC3, RC4;
    MiniLED LED1, LED2;
	MiniBTN BTN1, BTN2;
	MiniDIG D1, D2, D3, D4;
	MiniANG ANG1, ANG2, ANG3;
	MiniUS US1, US2, US3, US4;
};

#endif
