
/*************************************************************************
  File Name          : Matrix_mini_BT_Control_Uart.ino
  Author             : Frason
  Updated            : Frason
  Version            : V02.51.000
  Date               : 11/09/2018
  Description        : BT Control
  License            :
  Copyright (C) 2018 KK INTELLIGENT TECHNOLOGY INC.. All right reserved.
  http://www.matrixrobotics.com/
**************************************************************************/
#include <Wire.h>
#include <MatrixMini.h>
//#include <SoftwareSerial.h>

MatrixMini myMini;
//SoftwareSerial BT (6, 5);

String  Version = "02.51.000";
boolean isAvailable = false;
int pos1 = 90;
int pos2 = 90;
int pos3 = 90;
int pos4 = 90;
int r1, r2, b1, b2, g1, g2 = 0;
const int cmd = 3;
byte bf[cmd] = {0};
int RCFlag = 0;

#define key 1
#define value 2

#define Stop 2
#define Forward 3
#define Backward 4
#define GoLeft 5
#define GoRight 6
#define TurnLeft 7
#define TurnRight 8
#define LeftR 9
#define LeftG 10
#define LeftB 11
#define RightR 12
#define RightG 13
#define RightB 14
#define _RC1 15
#define _RC2 16
#define _RC3 17
#define _RC4 18


int pp = 0;
void setup() {
  Serial.begin(9600);
  myMini.begin();// Analog servos set at ~60 Hz updates
//  BT.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    Serial.readBytes(bf, cmd);
//    Serial.print(bf[0]);
//    Serial.print(":");
//    Serial.print(bf[key]);
//    Serial.print(":");
//    Serial.println(bf[value]);
  }
  if (bf[0] == 255) {
    switch (bf[key]) {
      // DCMOTOR
      case Forward:  //Forward
        myMini.M1.set(bf[value]);
        myMini.M2.set(bf[value]);
        break;
      case TurnLeft:  //Turn Left
        myMini.M1.set(-bf[value]);
        myMini.M2.set(bf[value]);
        break;
      case TurnRight:  //Turn Right
        myMini.M1.set(bf[value]);
        myMini.M2.set(-bf[value]);
        break;
      case Backward:  //Back
        myMini.M1.set(-bf[value]);
        myMini.M2.set(-bf[value]);
        break;
      case GoLeft:  //Go Left
        myMini.M1.set(0.8 * bf[value]);
        myMini.M2.set(bf[value]);
        break;
      case GoRight:  //Go Right
        myMini.M1.set(bf[value]);
        myMini.M2.set(0.8 * bf[value]);
        break;
      case Stop:
        myMini.M1.set(0);
        myMini.M2.set(0);
        break;

      // SERVO
      case _RC1:
        if (bf[value] == 201 && pos1 <= 180) {
          pos1++;
          myMini.RC1.set(pos1);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos1 >= 0) {
          pos1--;
          myMini.RC1.set(pos1);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value == 203]) {
          RCFlag = 0;
        }
        break;

      case _RC2:
        if (bf[value] == 201 && pos2 <= 180) {
          pos2++;
          myMini.RC2.set(pos2);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos2 >= 0) {
          pos2--;
          myMini.RC2.set(pos2);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value == 203]) {
          RCFlag = 0;
        }
        break;

      case _RC3:
        if (bf[value] == 201 && pos3 <= 180) {
          pos3+=2;
          myMini.RC3.set(pos3);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos3 >= 0) {
          pos3-=2;
          myMini.RC3.set(pos3);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value == 203]) {
          RCFlag = 0;
        }
        break;
        
      case _RC4:
        if (bf[value] == 201 && pos4 <= 180) {
          pos4+=2;
          myMini.RC4.set(pos4);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos4 >= 0) {
          pos4-=2;
          myMini.RC4.set(pos4);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value == 203]) {
          RCFlag = 0;
        }
        break;


      //RGB
      case LeftR:
        r1 = bf[value];
        break;
      case LeftG:
        g1 = bf[value];
        break;
      case LeftB:
        b1 = bf[value];
        break;
      case RightR:
        r2 = bf[value];
        break;
      case RightG:
        g2 = bf[value];
        break;
      case RightB:
        b2 = bf[value];
        break;

      default:
        myMini.M1.set(0);
        myMini.M2.set(0);
        break;
    }
  }
  myMini.LED1.setRGB(map(r1, 0, 255, 0, 4096), map(g1, 0, 255, 0, 4096), map(b1, 0, 255, 0, 4096));
  myMini.LED2.setRGB(map(r2, 0, 255, 0, 4096), map(g2, 0, 255, 0, 4096), map(b2, 0, 255, 0, 4096));
  if (RCFlag == 0) {
    for (int i = 0; i < cmd; i++) {
      bf[i] = 0;
    }
  }
}
