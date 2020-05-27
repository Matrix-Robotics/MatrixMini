/*******************
  Mini Analog Plotting Example
 * Description: Demonstrates how to use Serial Plotter to
 *              show how the analog input change.
 * Note:        After uploading the code, open the Serial Plotter
 *              insted of Serial Monitor.
 *               Tools-> Serial Plotter(Ctrl+Shift+L)
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
  Serial.println("\nMATRIX Mini Test - Analog Plotting\n");
  Serial.println("Starting Up ... ");
}

void loop() {
  Serial.print(Mini.ANG1.get());
  Serial.print(" ");
  Serial.println(Mini.ANG3.get());
}
