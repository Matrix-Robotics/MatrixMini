/*******************
  Mini Buttons & LED Example
 * Description: A simple application with Buttons & LEDs.
 *               Pressed buttons to light up the LEDs.
 *              
 * Author:      Frason Fan
 * modified 16 Dec 2019
 *  
 * www.matrixrobotics.com
*/
#include <MatrixMini.h>

MatrixMini Mini;

void setup() {
  Mini.begin(); 
  Serial.begin(9600);
  Serial.println("\nMatrix Mini Test - Buttons & LED\n");
  Serial.println("Starting Up ... ");
  delay(2000);
}

void loop() {
  if(Mini.BTN1.get()) 
    Mini.LED1.setRGB(255,0, 0);
  else
    Mini.LED1.setRGB(0,0, 0);


  if(Mini.BTN2.get()) 
    Mini.LED2.setRGB(0,255, 0);
  else
    Mini.LED2.setRGB(0,0, 0);
  
  delay(50);
}
