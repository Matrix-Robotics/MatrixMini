/////////////////////////// MINI Commands
#define _RST 0

#define _M1 0x1
#define _M2 0x2

#define _RC1 0x11
#define _RC2 0x12
#define _RC3 0x13
#define _RC4 0x14

#define _LED1 0x21
#define _LED2 0x22
#define _LEDR1 0x23
#define _LEDG1 0x24
#define _LEDB1 0x25
#define _LEDR2 0x26
#define _LEDG2 0x27
#define _LEDB2 0x28

#define _BTN1 0x31
#define _BTN2 0x32

#define _D1 0x41
#define _D2 0x42
#define _D3 0x43
#define _D4 0x44
#define _D5 0x45

#define _ANG1 0x51
#define _ANG2 0x52
#define _ANG3 0x53

//Customised Sensor Commands
#define _US1 0x81
#define _US2 0x82
#define _US3 0x83
#define _US4 0x84

//User Commands

///////////////////////////

#include <MatrixMini.h>
MatrixMini Mini;

#define RATE 10

unsigned long int myTimer = 0;

byte incomingByte;

byte msg = 0;
byte btnValue = 0;


void setup() {
  Mini.begin(); 
  Serial.begin(9600);
}


void loop() {
  if(millis() - myTimer > RATE){
    myTimer = millis();
    Send();
    Receive();    
  }
}






// Write Data to Serial
void Send(){
  ///////////////sendMessege(_M1, );
  ///////////////sendMessege(_M1, );
  ///////////////sendMessege(_RC1, );
  ///////////////sendMessege(_RC2, );
  ///////////////sendMessege(_RC3, );
  ///////////////sendMessege(_RC4, );
  ///////////////sendMessege(_LED1, );
  ///////////////sendMessege(_LED2, );
  sendMessege(_BTN1, Mini.BTN1.get());
  sendMessege(_BTN2, Mini.BTN2.get());
  //sendMessege(_D1, Mini.D1.get());
  //sendMessege(_D2, Mini.D2.get());
  //sendMessege(_D3, Mini.D3.get());
  //sendMessege(_D4, Mini.D4.get());
  //sendMessege(_ANG1, map(Mini.ANG1.get(), 0, 1023, 0, 254));
  //sendMessege(_ANG2, map(Mini.ANG2.get(), 0, 1023, 0, 254));
  //sendMessege(_ANG3, map(Mini.ANG3.get(), 0, 1023, 0, 254));
  sendMessege(_US1, Mini.US1.get());
  //sendMessege(_US2, Mini.US2.get());
  //sendMessege(_US3, Mini.US3.get());
  //sendMessege(_US4, Mini.US4.get());
  }


// send messege helper
byte* sendMessege(byte cmd, byte value){
  byte msg[3];
  msg[0] = 255;
  msg[1] = cmd;
  msg[2] = value;
  Serial.write(msg, 3);
  }


// Read data from Serial
void Receive(){
  while(Serial.available()>0){
        incomingByte = Serial.read();
        if(incomingByte!=255) continue;
        while(Serial.available()<2);
        byte field = Serial.read();
        byte value = Serial.read();

        // Compare field and apply value
        if(field==_RST);
        else if(field==_M1) Mini.M1.set((int8_t)value);
        else if(field==_M2) Mini.M2.set((int8_t)value);
        else if(field==_RC1) Mini.RC1.set(value);
        else if(field==_RC2) Mini.RC2.set(value);
        else if(field==_RC3) Mini.RC3.set(value);
        else if(field==_RC4) Mini.RC4.set(value);
        else if(field==_LED1) Mini.LED1.setHSV(map(value, 0, 254, 0, 360), 1.0, 1.0);
        else if(field==_LED2) Mini.LED2.setHSV(map(value, 0, 254, 0, 360), 1.0, 1.0);
        else if(field==_BTN1) ;
        else if(field==_BTN2) ;
        else if(field==_D1) Mini.D1.set(value);
        else if(field==_D2) Mini.D2.set(value);
        else if(field==_D3) Mini.D3.set(value);
        else if(field==_D4) Mini.D4.set(value);
        else if(field==_ANG1) Mini.ANG1.set(map(value, 0, 254, 0, 1023));
        else if(field==_ANG2) Mini.ANG2.set(map(value, 0, 254, 0, 1023));
        else if(field==_ANG3) Mini.ANG3.set(map(value, 0, 254, 0, 1023));
        else if(field==_US1) ;
        else if(field==_US2) ;
        else if(field==_US3) ;
        else if(field==_US4) ;
        else ;
   }
}
