/* CalibrateColorBalance - Color Sensor for use with the Core Spartan Controller
  (c) Modern Robotics Inc. 2016  http://www.modernroboticsinc.com
        
  The Color Sensor uses various channels of color to determine the approximate color of an 
  object. This data includes a color number that corresponds to the color line in the 
  documentation, as well as raw and adjusted readings. Best results will be attained in a 
  well-lit area and the object no more than 7cm away from the sensor. 
  
  This example calibrates the white and black balance values used when calculating normalized 
  color readings.Upload the sketch to your Spartan, connect your touch and color sensors, open 
  the serial monitor using CTRL+SHIFT+M, and follow the prompts on your screen. Refer to the 
  documentation for more information on calibrating and descriptions of the returned values.

  Modified by KKITC for use of Matrix Mini Controller
-------------------------------------------------------------------------------------------*/
#include <MatrixMini.h>

MatrixMini Mini;
MiniCoreColor ColorSensor;

byte r,g,b,grayscale;
void setup(){
  Mini.begin();
  ColorSensor.begin();
  Serial.begin(9600);
  
  Serial.println("\n Matrix Mini Color Balance Calibrations\n");
  Mini.LED1.setRGB(0,0,0);        //LED1 is set emtpy for black level's button indication
  Mini.LED2.setRGB(200,200,200);  //LED2 is set white for white balance's button indication
  // When the touch sensor is pressed, calibrate the black balance value
  Serial.println("Hold the sensor pointing to empty space");
  Serial.println("Press Mini Button 1 to calibrate Black Balance");
  while(!Mini.BTN1.get());
  ColorSensor.setBlackLevel();
  delay(1000);
  
  // When the touch sensor is pressed, calibrate the white balance value
  Serial.println("Hold the sensor approximately 2 inches away from white target");
  Serial.println("Press Mini Button 2 to calibrate White Balance");
  while(!Mini.BTN2.get());
  ColorSensor.setWhiteBalance();
  delay(1000);
  
  Serial.println("Done! The COLOR Sensor can now be used to read color values");
  Serial.println("using examples or user generated code. Reset or download a");
  Serial.println("new sketch to continue");
}

void loop(){
  // Wait here till user resets or downloads a new program.
}
