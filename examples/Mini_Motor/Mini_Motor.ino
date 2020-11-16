/*
  Mini Motor Example
 * Description: Demonstrates how to use Motor Commands.
 *   
 * Author:      Frason Fan
 * modified 16 Nov 2020
 *
 * www.matrixrobotics.com
 */
#include <MatrixMini.h>

void setup() {
  Mini.begin();  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("\nMatrix Mini Test - DC Motor\n");
  Serial.println("Starting Up ... ");
  Mini.M1.set(0);
  Mini.M2.set(0);
  delay(2000);
}

void loop() {
  int i;
  
  Serial.println("One way");
  for (i=0; i<100; i++) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  for (i=100; i>0; i--) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  delay(500);
  Serial.println("Or another");
  for (i=0; i>-100; i--) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  for (i=-100; i<0; i++) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  delay(500);
}
