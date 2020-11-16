/*******************
  Mini RGB Example
 * Description: Demonstrates how to use RGBLED Commands to change color.
 *               We provide two controlling method, RGB and HSV mode.
 *
 * Author:      Frason Fan
 * modified 16 Dec 2019
 *  
 * www.matrixrobotics.com
*/
#include <MatrixMini.h>
int hue, dir;
float sat, val;

void setup() {
  Mini.begin();
  Serial.begin(9600);       
  Serial.println("\nMatrix MINI Test - RGB LED\n");
  Serial.println("Starting Up ... ");
  dir = 1;
  hue = 50;
  sat = 1.0;
  val = 1.0;
  
  Mini.RGB1.setRGB(0, 0, 0);
  Mini.RGB2.setHSV(hue, sat, val);
  
  randomSeed(analogRead(0));
  delay(2000);
}

void loop() {
  // Blink first RGB
  if (millis()/600 % 2)
    Mini.RGB1.setRGB(255, 0, 0);
  else 
    Mini.RGB1.setRGB(0, 0, 255);

  // Color Hue for Second RGB
  hue += dir * random(1, 5);
  if( hue > 359 || hue < 0) dir = -dir;
  hue = constrain(hue, 0, 359);
  Mini.RGB2.setHSV(hue, sat, val);
  
  Serial.print(" HUE: ");
  Serial.println(hue);

  delay(30);
}
