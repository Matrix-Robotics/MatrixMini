/******************************************************************
 ******************************************************************/

#ifndef _MiniSerial_h_
#define _MiniSerial_h_

#include "Arduino.h"
#include "MiniSerialConstants.h"

void sendMessageBuf(byte, byte, byte*);
void sendMessage(byte, byte);

#endif
