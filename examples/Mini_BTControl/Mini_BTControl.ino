/*******************
  Mini Bluetooth Remote Control Example
 * Description: A simple application with Bluetooth module and APP by AI2.
 * Note:        Download the remote control APP from Matrix Robotics website.             
 *              
 * Author:      Frason Fan
 * modified 18 Nov 2020
 *  
 * www.matrixrobotics.com
*/

#include <Wire.h>
#include <MatrixMini.h>
#include <SoftwareSerial.h>

SoftwareSerial BT (6, 5); // Bluetooth module on D4

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
  Serial.begin(115200);
  Mini.begin();
  BT.begin(9600);
}

void loop() {
  if (BT.available() > 0) {
    BT.readBytes(bf, cmd);
  }
  if (bf[0] == 255) {
    switch (bf[key]) {
      // DCMOTOR
      case Forward:  //Forward
        Mini.M1.set(bf[value]);
        Mini.M2.set(bf[value]);
        break;
      case TurnLeft:  //Turn Left
        Mini.M1.set(-bf[value]);
        Mini.M2.set(bf[value]);
        break;
      case TurnRight:  //Turn Right
        Mini.M1.set(bf[value]);
        Mini.M2.set(-bf[value]);
        break;
      case Backward:  //Back
        Mini.M1.set(-bf[value]);
        Mini.M2.set(-bf[value]);
        break;
      case GoLeft:  //Go Left
        Mini.M1.set(0.8 * bf[value]);
        Mini.M2.set(bf[value]);
        break;
      case GoRight:  //Go Right
        Mini.M1.set(bf[value]);
        Mini.M2.set(0.8 * bf[value]);
        break;
      case Stop:
        Mini.M1.set(0);
        Mini.M2.set(0);
        break;

      // SERVO
      case _RC1:
        if (bf[value] == 201 && pos1 <= 180) {
          pos1++;
          Mini.RC1.set(pos1);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos1 >= 0) {
          pos1--;
          Mini.RC1.set(pos1);
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
          Mini.RC2.set(pos2);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos2 >= 0) {
          pos2--;
          Mini.RC2.set(pos2);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value == 203]) {
          RCFlag = 0;
        }
        break;

      case _RC3:
        if (bf[value] == 201 && pos3 <= 180) {
          pos3 += 2;
          Mini.RC3.set(pos3);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos3 >= 0) {
          pos3 -= 2;
          Mini.RC3.set(pos3);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value == 203]) {
          RCFlag = 0;
        }
        break;

      case _RC4:
        if (bf[value] == 201 && pos4 <= 180) {
          pos4 += 2;
          Mini.RC4.set(pos4);
          delay(10);
          RCFlag = 1;
        }
        else if (bf[value] == 202 && pos4 >= 0) {
          pos4 -= 2;
          Mini.RC4.set(pos4);
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
        Mini.M1.set(0);
        Mini.M2.set(0);
        break;
    }
  }
  Mini.RGB1.setRGB(r1, g1, b1);
  Mini.RGB2.setRGB(r2, g2, b2);
  if (RCFlag == 0) {
    for (int i = 0; i < cmd; i++) {
      bf[i] = 0;
    }
  }
}
