#include "BATTERY.h"

int UARTbuffer = -1;
bool UART_IT = false;

int version = 1;

float DET_VBAT = 7.4;
int VBAT_toggle_flag = 0;
float DET_vcc = 0;
int vcc_cont = 0;
int VBAT_flag = 1;

int encLtA, encLtB, encRtA, encRtB;
long encLt, encRt;
// volatile bool ENCO_flag = false;

ISR(TIMER2_COMPA_vect){
    Encoderead();

    if(VBAT_flag){
        VBAT_check();
        if (UART_IT) {
            if (UARTbuffer == -1){
                Serial.println("error");
            }
            else{
                Serial.println(UARTbuffer, 16);
            }
            UART_IT = false;
        }
    }
}

void VBAT_check(){
    vcc_cont++;

    if(vcc_cont >= 15){
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
    }
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
    default:
        break;
    }
}

void set_VBAT(float vbat, int ver){
    DET_VBAT = vbat;
    version = ver;
}

void serialSendBuffer(int buf){
    UARTbuffer = buf;
}

void sendEnable(){
    UART_IT = true;
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
/*

void Encoder::Init(int portL, int portR){

    if(ver == 3){
        setPWM_PCA9685(6, 0, 4095, 0); 
    }

    cli();

    TCCR2B = 2;
    // set prescaler to 1/8 and starts PWM

    TIMSK2 = 2;
    //Set interrupt on compare match

    sei();

    VBAT_flag =0;


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
}

float Encoder::get_Angle(int M, int ppr){
    switch (M)
    {
    case ENL:
        return abs((encLt%ppr)*360/ppr);
        break;
    
    case ENR:
        return abs((encRt%ppr)*360/ppr);
        break;
    }
}

float Encoder::get_Turn(int M, int ppr){
    switch (M)
    {
    case ENL:
        return float(encLt)/ppr;
        break;
    
    case ENR:
        return float(encRt)/ppr;
        break;
    }
}

float Encoder::get_Distance(int M, float diameter){

    return  get_Turn(M) * diameter * PI;
}
*/