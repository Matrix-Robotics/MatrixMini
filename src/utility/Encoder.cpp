#include "Encoder.h"
 
int encLtA, encLtB, encRtA, encRtB;
long encLt, encRt;
volatile bool ENCO_flag = false;
int version;

float DET_VBAT;
int VBAT_toggle_flag = 0;
float DET_vcc;
int vcc_cont = 0;

ISR(TIMER2_COMPA_vect){
    
    Encoderead();
    VBAT_check();
}

void Encoderead(){
    int8_t val, diff;

    val = 0;

    if(digitalRead(encLtA)){
        val = 3;
    }
    if(digitalRead(encLtB)){
        val ^= 1;					// convert gray to binary
    }
    diff = lastLt - val;				// difference last - new

    if( diff & 1 ){				// bit 0 = value (1)
        lastLt = val;				// store new as next last
        encDeltaLt += (diff & 2) - 1;		// bit 1 = direction (+/-)
    }

    val = 0;

    if(digitalRead(encRtA)){
        val = 3;
    }
    if(digitalRead(encRtB)){
        val ^= 1;					// convert gray to binary
    }
    diff = lastRt - val;				// difference last - new

    if( diff & 1 ){				// bit 0 = value (1)
        lastRt = val;				// store new as next last
        encDeltaRt += (diff & 2) - 1;		// bit 1 = direction (+/-)
    }

    encLt += ReadLt();
    encRt += ReadRt();
}


int8_t ReadLt( void ){

    int8_t val;

    cli();

    val = encDeltaLt;
    encDeltaLt = 0;

    sei();
    
    return val;					// counts since last call
}


int8_t ReadRt( void ){

    int8_t val;

    cli();

    val = encDeltaRt;
    encDeltaRt = 0;

    sei();

    return val;					// counts since last call
}

void BAT_Det(){
    
    switch (version)
    { 
    case 2:
        if(DET_vcc > DET_VBAT){
            setPWM_PCA9685(6, 0);
        }
        else if(((DET_VBAT*0.95) < DET_vcc) & (DET_vcc < DET_VBAT)){
            setPWM_PCA9685(6, 4095);
        }
        else{
            if(VBAT_toggle_flag){
                setPWM_PCA9685(6, 4095);
                VBAT_toggle_flag = 0;
            }
            else{
                setPWM_PCA9685(6, 0);
                VBAT_toggle_flag = 1;
            }
        }
        break;
    case 3:
        if(DET_vcc > DET_VBAT){
            setPWM_PCA9685(9, 4095);
        }
        else if(((DET_VBAT*0.95) < DET_vcc) & (DET_vcc < DET_VBAT)){
            setPWM_PCA9685(9, 0);
            setPWM_PCA9685(8, 4095);
        }
        else{
            if(VBAT_toggle_flag){
                setPWM_PCA9685(9, 0);
                setPWM_PCA9685(8, 4095);
                VBAT_toggle_flag = 0;
            }
            else{
                setPWM_PCA9685(9, 0);
                setPWM_PCA9685(8, 0);
                VBAT_toggle_flag = 1;
            }
        }
        break;
    default:
        break;
    }
}
void VBAT_check(){
    vcc_cont++;

    if(vcc_cont >= 500){
        switch (version)
        {
        case 2:
            DET_vcc = (float(analogRead(A6))/1024*5.03*4)+0.3;
            break;
        case 3:
            DET_vcc = float(analogRead(A3))/1024*5*5.545;   
            break;
        default:
            break;
        }
        BAT_Det();
        vcc_cont = 0;
        //Serial.println(DET_vcc);
    }
    
    
}
void set_VBAT(float vbat){
    DET_VBAT = vbat;
}


void Encoder::Init(int portL, int portR){
    // cli();

    // TCCR2B = 2;
    // // set prescaler to 64 and starts PWM

    // TIMSK2 = 2;
    // //Set interrupt on compare match

    // sei();

    det_pinL(portL);
    det_pinR(portR);

    int8_t val;

    val=0;

    if (digitalRead(encLtA)){
        val = 3;
    }
    if (digitalRead(encLtB)){
        val ^= 1;
    }

    lastLt = val;

    encDeltaLt = 0;

    val=0;

    if (digitalRead(encRtA)){
        val = 3;
    }
    if (digitalRead(encRtB)){
        val ^= 1;
    }

    lastRt = val;

    encDeltaRt = 0;

    encLt = 0;
    encRt = 0;

    cli();

    ENCO_flag = true;

    sei();
}

int Encoder::det_pinL(int port){
    switch (ver)
    {
    case 1:
        switch (port)
        {
        case 1:
            encLtA = 2;
            encLtB = 3;
            break;
        case 2:
            encLtA = 3;
            encLtB = 4;
            break;        
        case 3:
            encLtA = 4;
            encLtB = 5;
            break;        
        case 4:
            encLtA = 5;
            encLtB = 6;
            break;
        }
        break;
    case 2:
        switch (port)
        {
        case 1:
            encLtA = 2;
            encLtB = 3;
            break;
        case 2:
            encLtA = 3;
            encLtB = 4;
            break;        
        case 3:
            encLtA = 4;
            encLtB = 5;
            break;         
        case 4:
            encLtA = 5;
            encLtB = 12;
            break;
        }
        break;

    case 3:
        switch (port)
        {
        case 1:
            encLtA = 5;
            encLtB = 6;
            break;
        case 2:
            encLtA = 7;
            encLtB = 9;
            break;        
        case 3:
            encLtA = 10;
            encLtB = 11;
            break;        
        case 4:
            encLtA = 12;
            encLtB = 13;
            break;
        }
        break;
    }
}

int Encoder::det_pinR(int port){
    switch (ver)
    {
    case 1:
        switch (port)
        {
        case 1:
            encRtA = 2;
            encRtB = 3;
            break;
        case 2:
            encRtA = 3;
            encRtB = 4;
            break;        
        case 3:
            encRtA = 4;
            encRtB = 5;
            break;        
        case 4:
            encRtA = 5;
            encRtB = 6;
            break;
        }
        break;
    case 2:
        switch (port)
        {
        case 1:
            encRtA = 2;
            encRtB = 3;
            break;
        case 2:
            encRtA = 3;
            encRtB = 4;
            break;        
        case 3:
            encRtA = 4;
            encRtB = 5;
            break;         
        case 4:
            encRtA = 5;
            encRtB = 12;
            break;
        }
        break;

    case 3:
        switch (port)
        {
        case 1:
            encRtA = 5;
            encRtB = 6;
            break;
        case 2:
            encRtA = 7;
            encRtB = 9;
            break;        
        case 3:
            encRtA = 10;
            encRtB = 11;
            break;        
        case 4:
            encRtA = 12;
            encRtB = 13;
            break;
        }
        break;
    }
}
void Encoder::begin(int _ver){
    ver = _ver;
    version = _ver;
}

float Encoder::get_Angle(int M, int ppr){
    switch (M)
    {
    case L:
        return abs((encLt%ppr)*360/ppr);
        break;
    
    case R:
        return abs((encRt%ppr)*360/ppr);
        break;
    }
}

float Encoder::get_Turn(int M, int ppr){
    switch (M)
    {
    case L:
        return float(encLt)/ppr;
        break;
    
    case R:
        return float(encRt)/ppr;
        break;
    }
}

float Encoder::get_Distance(int M, float diameter){

    return  get_Turn(M) * diameter * PI;
}