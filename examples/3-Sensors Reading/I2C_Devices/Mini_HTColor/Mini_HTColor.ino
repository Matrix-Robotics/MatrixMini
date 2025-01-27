/*******************
  Mini Hitechnic Color Sensor Example
   Description: Demonstrates how to use Hitechnic Color Sensor.

   Author:      Frason Fan
   modified 20 Apr 2021

   www.matrixrobotics.com
*/
#include <MatrixMini.h>

void setup() {
  Mini.begin();
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("\nMatrix Mini Test - Hitechnic Color Sensor\n");
  Serial.println("Hitechnic Color Sensor on I2C port 1 ");
}

void loop() {
  Serial.print("Get Red : ");
  Serial.println(Mini.I2C1.HTcolor.getR());
  Serial.print("Get Green : ");
  Serial.println(Mini.I2C1.HTcolor.getG());
  Serial.print("Get Blue : ");
  Serial.println(Mini.I2C1.HTcolor.getB());
  //  Get Color RGB Function returns a number from 0 to 255
  Serial.println("=================");

  Serial.print("Get Color Number : ");
  Serial.println(Mini.I2C1.HTcolor.getColorNumber());
  //  Get Color Number Function returns a number from 0 to 16
  //  you can check with the image in the folder
  Serial.println("=================");

  Serial.print("Get Grayscale : ");
  Serial.println(Mini.I2C1.HTcolor.getGrayscale());
  //  Get Grayscale Function returns a number from 0 to 255
  //  Grayscale representing an amount of light, which can be roughly considerd as brightness
  Serial.println("=================");

  delay(500);
}
