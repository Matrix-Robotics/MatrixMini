/*******************
  Mini Servo Example
 * Description: Demonstrates how to use Servo Commands to change the angle of servos.
 *
 * Author:      Frason Fan
 * modified 18 Nov 2020
 *  
 * www.matrixrobotics.com
 */
#include <MatrixMini.h>

void setup() {
  Mini.begin();
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("\nMatrix Mini Test - Servo\n");
  
  // Range 0 to 180 deg
  Mini.RC1.set(0);
  Mini.RC2.set(0);
  Mini.RC3.set(0);
  Mini.RC4.set(0);
}

void loop() {
  int i;
  Serial.println("One way");
  Mini.RC1.set(0);
  Mini.RC2.set(0);
  for (i = 0; i < 180; i++) {
    Mini.RC3.set(i); 
    Mini.RC4.set(i); 
    delay(10);
  }
  delay(500);
  Mini.RC1.set(180);
  Mini.RC2.set(180);
  Serial.println("Or another");
  for (i = 180; i > 0; i--) {
    Mini.RC3.set(i);  
    Mini.RC4.set(i); 
    delay(10);
  }
  delay(500);
}
