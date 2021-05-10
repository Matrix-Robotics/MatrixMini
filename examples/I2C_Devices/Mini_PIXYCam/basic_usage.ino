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

  // sigmap means allow signature range
  // Ex: sigmap = 3, means allowed signatures are: 1, 2, 3. (max is 7)
  Mini.I2C1.PIXYcam.pixyinit(3);
}
int i=0;

void loop() {
  // Get specific signature, with n_th largest block.
  // Note: getblock(signature, n_th) should be use before other functions.
  // getblock(0, 1) means select the largest block with no specific signature.
  bool isBlockValid = Mini.I2C1.PIXYcam.getblock(0, 1);
  if (isBlockValid==true)
  {
    Serial.print("Num of Frames: ");
    Serial.println(i);
    i ++;

    ////////////////////////////////
    ////// PIXYCam Functions //////
    ///////////////////////////////

    // .getCountofBlock(): Count of received blocks, default max is 8 .
    Serial.print("Count of blocks : ");
    Serial.println(Mini.I2C1.PIXYcam.getCountofBlock());

    ///////////////////////////////////
    ////// ColorBlock properties //////
    ///////////////////////////////////

    // .signature: The signature number of the detected object (1-7 for normal signatures)
    // Note: If you got signature = 0, means no blocks.
    Serial.print("block's signature : ");
    Serial.println(Mini.I2C1.PIXYcam.block.signature);

    // .x: The x location of the center of the detected object (0 to 316)
    Serial.print("x position: ");
    Serial.println(Mini.I2C1.PIXYcam.block.x);
    // .y: The y location of the center of the detected object (0 to 208)
    Serial.print("y position: ");
    Serial.println(Mini.I2C1.PIXYcam.block.y);

    // .width: The width of the detected object (1 to 316)
    Serial.print("width: ");
    Serial.println(Mini.I2C1.PIXYcam.block.width);
    // .height: The height of the detected object (1 to 208)
    Serial.print("height: ");
    Serial.println(Mini.I2C1.PIXYcam.block.height);

    // .angle: The angle of the object detected object if the detected object is a color code (-180 to 180).
    Serial.print("angle: ");
    Serial.println(Mini.I2C1.PIXYcam.block.angle);

    // .index :The tracking index of the block
    Serial.print("index: ");
    Serial.println(Mini.I2C1.PIXYcam.block.index);
    // .age: The number of frames the block has been tracked.
    Serial.print("age: ");
    Serial.println(Mini.I2C1.PIXYcam.block.age);
    Serial.println("=================");
    delay(100);
  }
}
