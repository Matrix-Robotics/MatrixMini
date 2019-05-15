/***************************************************
 ****************************************************/
#include "MiniSerial.h"
// send message helper for multiple data
void sendMessageBuf(byte field, byte numBytes, byte* dataBuf){
  byte msg[2];
  msg[0] = START_SYSEX;
  msg[1] = field;
  Serial.write(msg, 2);
  Serial.write(dataBuf, numBytes);
}

// send message helper
// Onboard data are all in 3 bytes
void sendMessage(byte field, byte value){
   byte msg[3];
   msg[0] = START_SYSEX;
   msg[1] = field;
   msg[2] = value;
   Serial.write(msg, 3);
}
