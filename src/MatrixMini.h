/******************************************************************
 *  MatrixMini.h
 *
 * Written by KKITC RD Team
 * BSD license, all text here must be included in any redistribution.
 *
 ******************************************************************/

#ifndef _MatrixMini_h_
#define _MatrixMini_h_

#include <Arduino.h>
#include "MiniDC.h"
#include "MiniLED.h"
#include "MiniBTN.h"
#include "MiniDIG.h"
#include "MiniANG.h"
#include "MiniRC.h"
#include "I2C/MiniI2C.h"
#include "utility/Encoder.h"

#define det_pin 8

#define AA_6 8.1
#define LI_2 7.4
#define LI_3 11.1
#define LI_2 14.8
#define LI_3 18.5
#define LI_6 22.2


class MatrixMini_{
private:
    int v3_check();
    void det_version();
    void init();
    int _ver;
    
public:
    void begin(float vbat = AA_6);
    
    // Modules
    MiniDC  M1, M2;
    MiniRC  RC1, RC2, RC3, RC4;
    MiniLED RGB1, RGB2;
	MiniBTN BTN1, BTN2;
	MiniDIG D1, D2, D3, D4;
	MiniANG A1, A2, A3;
    MiniI2C I2C1, I2C2, I2C3, I2C4;
    Encoder ENCO;
};
extern MatrixMini_ Mini;

#endif
