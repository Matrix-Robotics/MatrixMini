/*******************
  Mini RGB Example
 * Description: Demonstrates how to use RGBLED Commands to change color.
 *               We provide two controlling method, RGB and HSV mode.
 *
 * Author:      Frason Fan
 * modified 17 Nov 2020
 *  
 * www.matrixrobotics.com
*/
#include <MatrixMini.h>
int hue, dir;
float sat, val;

void setup() {
  Mini.begin();
  Serial.begin(115200);       
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
  unsigned int i = millis();
  Serial.print("Time: ");  Serial.println(i);
  if (i / 600 % 2)
    Mini.RGB1.setRGB(255, 0, 0);
  else 
    Mini.RGB1.setRGB(0, 0, 255);

  // Color Hue for Second RGB
  hue=millis() / 20 % 360;
  Mini.RGB2.setHSV(hue,sat,val);

  Serial.print(" HUE: ");
  Serial.println(hue);
  Serial.println("=====================================");
  delay(10);
}
