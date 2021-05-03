/*******************
  Mini PIXY2 Cam Example
   Description: Demonstrates how to use PIXY2 Cam.

   Author:      Ryan Cheng
   modified 01 May 2021

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

  for (int i=0; i<2; i++){
    //  Get n largest color block, captured by PIXY Cam.
    //  0 is the largest, 1 is smaller then 0 color block, and so on.
    Mini.I2C1.PIXYcam.getblock(i);
    //  .print(): A member function that prints the detected object information to the serial port
    Mini.I2C1.PIXYcam.block.print();

    Serial.print(i);
    Serial.println(" largest color block");

    //  .m_signature: The signature number of the detected object (1-7 for normal signatures)
    Serial.print("Get block sig : ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_signature);

    //  .m_x: The x location of the center of the detected object (0 to 316)
    Serial.print("Get block x position: ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_x);
    //  .m_y: The y location of the center of the detected object (0 to 208)
    Serial.print("Get block y position: ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_y);

    //  .m_width: The width of the detected object (1 to 316)
    Serial.print("Get block width: ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_width);
    //  .m_height: The height of the detected object (1 to 208)
    Serial.print("Get block height: ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_height);

    //  .m_angle: The angle of the object detected object if the detected object is a color code (-180 to 180).
    Serial.print("Get block angle: ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_angle);

    //  .m_index :The tracking index of the block
    Serial.print("Get block index: ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_index);
    //  .m_age: The number of frames the block has been tracked.

    Serial.print("Get block age: ");
    Serial.println(Mini.I2C1.PIXYcam.block.m_age);

    Serial.println("=================");
    
    delay(100);
  }


}