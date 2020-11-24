/*
  Mini Analog Read Example 
 * Description: Demonstrates how to read values from analog port.
 *   
 * Author:      Frason Fan
 * modified 18 Nov 2020
 *
 * www.matrixrobotics.com
 */
#include "MatrixMini.h"

void setup() {
  Mini.begin();
  Serial.begin(115200);
  Serial.println("\nMATRIX Mini Test - Analog Read\n");
  Serial.println("Starting Up ... ");
  delay(2000);
}

void loop() {
  Serial.print("A1 Port Read: ");  Serial.println(Mini.A1.get());
  Serial.print("A3 Port Read: ");  Serial.println(Mini.A3.get());
  Serial.println("---");
  delay(2000);
}
