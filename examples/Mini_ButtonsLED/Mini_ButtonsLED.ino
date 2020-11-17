/*******************
  Mini Buttons & LED Example
 * Description: A simple application with Buttons & LEDs.
 *               Pressed buttons to light up the LEDs.
 *              
 * Author:      Frason Fan
 * modified 17 Nov 2020
 *  
 * www.matrixrobotics.com
*/
#include <MatrixMini.h>

void setup() {
  Mini.begin(); 
  Serial.begin(9600);
  Serial.println("\nMatrix Mini Test - Buttons & LED\n");
  Serial.println("Starting Up ... ");
  delay(2000);
}

void loop() {
  if(Mini.BTN1.get()) 
    Mini.RGB1.setRGB(255,0, 0);
  else
    Mini.RGB1.setRGB(0,0, 0);

  if(Mini.BTN2.get()) 
    Mini.RGB2.setRGB(0,255, 0);
  else
    Mini.RGB2.setRGB(0,0, 0);
  delay(50);
}
