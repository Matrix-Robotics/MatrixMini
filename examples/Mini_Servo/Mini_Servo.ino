/*******************
  Mini Servo Example
 * Description: Demonstrates how to use Servo Commands to change the angle of servos.
 *
 * Author:      Frason Fan
 * modified 16 Dec 2019
 *  
 * www.matrixrobotics.com
 */
#include <MatrixMini.h>

void setup() {
  Mini.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("\nMatrix Mini Test - Servo\n");
  
  // Range 0 to 180 deg
  Mini.RC1.set(0);
  Mini.RC4.set(0);
}

void loop() {
  int i;
  Serial.println("One way");
  for (i=0; i<180; i++) {
    Mini.RC1.set(i); 
    Mini.RC4.set(i); 
    delay(15);
  }
  delay(500);
  Serial.println("Or another");
  for (i=180; i>0; i--) {
    Mini.RC1.set(i);  
    Mini.RC4.set(i); 
    delay(15);
  }
  delay(500);
}
