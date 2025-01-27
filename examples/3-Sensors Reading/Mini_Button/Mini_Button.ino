/*
  Mini Motor Example
 * Description: Demonstrates how to use Button Commands.
 *   
 * Author:      Frason Fan
 * modified 16 Dec 2019
 *
 * www.matrixrobotics.com
 */
#include <MatrixMini.h>

void setup() {
  Mini.begin(); 
  Serial.begin(115200);

  Serial.println("\n Matrix Mini Test - Button\n");
}

void loop() {
  Serial.print("  Button 1: "); Serial.print(Mini.BTN1.get());
  Serial.print("\tButton 2: "); Serial.print(Mini.BTN2.get());
  Serial.println();
  delay(50);
}
