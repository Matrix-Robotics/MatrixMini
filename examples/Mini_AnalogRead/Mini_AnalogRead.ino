/*
  Mini Analog Read Example 
 * Description: Demonstrates how to read values from analog port.
 *   
 * Author:      Frason Fan
 * modified 16 Dec 2019
 *
 * www.matrixrobotics.com
 */
#include "MatrixMini.h"

MatrixMini Mini;

void setup() {
  Mini.begin();
  Serial.begin(9600);
  Serial.println("\nMATRIX Mini Test - Analog Read\n");
  Serial.println("Starting Up ... ");
  delay(2000);
}

void loop() {
  Serial.print("A1 Port Read: ");  Serial.println(Mini.ANG1.get());
  Serial.print("A3 Port Read: ");  Serial.println(Mini.ANG3.get());
  Serial.println("---");
  delay(2000);
}
