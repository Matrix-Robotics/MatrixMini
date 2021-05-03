/*******************
  Mini PIXY2 Cam Example
   Description: Demonstrates how to use PIXY2 Cam.

   Author:      Ryan Cheng
   modified 03 May 2021

   www.matrixrobotics.com
*/
#include <MatrixMini.h>

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Mini.begin();
  Serial.println("\nMatrix Mini Test - PIXY2 Camera\n");
  Serial.println("PIXY2 Camera on I2C port 1 ");

}

void loop() {
 // Get n largest color block, captured by PIXY Cam.
 // 0 th is the largest color block.
 Mini.I2C1.PIXYcam.getblock(0);
// .print(): A member function that prints the detected object information to the serial port
 Mini.I2C1.PIXYcam.block.print();

// .m_signature: The signature number of the detected object (1-7 for normal signatures)
// .m_x: The x location of the center of the detected object (0 to 316)
// .m_y: The y location of the center of the detected object (0 to 208)
// .m_width: The width of the detected object (1 to 316)
// .m_height: The height of the detected object (1 to 208)
// .m_angle: The angle of the object detected object if the detected object is a color code (-180 to 180).
// .m_index :The tracking index of the block
// .m_age: The number of frames the block has been tracked.
 Serial.print("largest block width : ");
 Serial.println(Mini.I2C1.PIXYcam.block.m_width);
 Serial.println("=================");
 
 delay(100);
}