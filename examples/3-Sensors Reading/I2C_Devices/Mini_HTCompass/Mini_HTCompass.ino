/*******************
  Mini Hitechnic Compass Sensor Example
   Description: Demonstrates how to use Hitechnic Compass Sensor.

   Author:      Frason Fan
   modified 20 Apr 2021

   www.matrixrobotics.com
*/
#include <MatrixMini.h>

void setup() {
  Mini.begin();
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("\nMatrix Mini Test - Hitechnic Compass Sensor\n");
  Serial.println("Hitechnic Compass Sensor on I2C port 1 ");
}

void loop() {
  Serial.print("Get Red : ");
  Serial.println(Mini.I2C1.HTcompass.getHeading());
  //  Get Heading Function returns a number from 0 to 359
  Serial.println("=================");

  delay(500);
}
