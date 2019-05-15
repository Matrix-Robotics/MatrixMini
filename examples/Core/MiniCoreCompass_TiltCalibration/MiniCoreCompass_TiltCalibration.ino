/* CalibrateTilt - Compass calibration for use with Core Spartan Controller
  Modern Robotics Inc. 2016  http://www.modernroboticsinc.com
  
  The Compass uses a magnetometer and accelerometer to produce heading data. The sensor 
  should be calibrated before every use. Magnets or anything that can generate a magnetic 
  field will affect the readings of this sensor. The Compass can return heading data, 
  accelerometer data and magnetometer data on the x, y and z axis.
  
  This example will calibrate the tilt for the magnetometer. This is important because the 
  magnetic field is not on a horizontal plane, it is angle depending on the latitude at which 
  the sensor is being used. First, the sensor must be tilted up at 20 degrees and held there 
  during the calibration process. Next, the sensor must be angled down at an angle of 20 
  degrees. It is very important that the tilt up calibration is completed before the tilt 
  down calibration.

  Modified by Ning on 3/11/2019 for Matrix Mini Controller
-------------------------------------------------------------------------------------------*/
#include <MatrixMini.h>

MatrixMini Mini;

void setup(){
  Mini.begin();
  CompassSensor.begin();
  Serial.begin(9600);

  // Calibrate Compass to be level on a horizontal surface
  Serial.println("Tilt Calibration");
  Serial.println("  1. Tilt sensor up at an angle of 20 degrees");
  Serial.println("    Push Mini Button 1 to calibrate");
  while(!Mini.BTN1.get());
  CompassSensor.tiltUp();
  Serial.println("  2. Tilt sensor down at an angle of 20 degrees");
  Serial.println("    Push Mini Button 1 to calibrate");
  while(!Mini.BTN1.get());
  CompassSensor.tiltDown();
  Serial.println("*Tilt Calibration Complete*");
}

void loop(){
}

