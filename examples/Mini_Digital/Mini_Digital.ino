/*
  Mini Digital Port Example
 * Description: Demonstrates how to read values from and set out put 
 *               through digital ports.
 *
 * Author:      Frason Fan
 * modified 16 DEC 2019
 *
 * www.matrixrobotics.com
*/
#include "MatrixMini.h"

void setup() {
  Mini.begin();
  Serial.begin(115200);
  Serial.println("\nMATRIX Mini Test - Digital Read/ Set\n");
  Serial.println("Starting Up ... ");
  delay(2000);
}

void loop() {
  Serial.print("D1 Port Read: ");  Serial.println(Mini.D1.get());
  Serial.print("D2 Port Read: ");  Serial.println(Mini.D2.get());
  Serial.println("---");
  Serial.print("D3 Port Set: 0");  
  Serial.println("D4 Port Set: 0");
  Serial.println("---");
  Mini.D3.set(0);
  Mini.D4.set(0);
  delay(500);  
  Serial.print("D3 Port Set: 1");  
  Serial.println("D4 Port Set: 1");
  Serial.println("---");
  Mini.D3.set(1);
  Mini.D4.set(1);
  delay(500);
}
