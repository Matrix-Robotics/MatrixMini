#ifndef _Encoder_h_
#define _Encoder_h_

#include <Arduino.h>
#include "PCA9685.h"

#define L 0x99
#define R 0x98

int8_t ReadLt();
int8_t ReadRt();

void BAT_Det();
void set_VBAT(float vbat);
void VBAT_check();
void Encoderead();

static int8_t lastLt, lastRt;

static volatile int8_t encDeltaLt, encDeltaRt;

class Encoder{
private:

    int det_pinL(int port);
    int det_pinR(int port);
    int ver;
    void begin(int _ver);
    
public:
	friend class MatrixMini_;
    
    float get_Turn(int M, int ppr=660);
    float get_Angle(int M, int ppr=660);
    float get_Distance(int M, float diameter=6.6);
    void Init(int portL, int portR);
};

#endif