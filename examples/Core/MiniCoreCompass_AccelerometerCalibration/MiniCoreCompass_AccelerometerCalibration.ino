/* CalibrateAccelerometer - Compass calibration for use with Core Spartan Controller
  Modern Robotics Inc. 2016  http://www.modernroboticsinc.com
    
  The Compass uses a magnetometer and accelerometer to produce heading data. The sensor 
  should be calibrated before every use. Magnets or anything that can generate a magnetic 
  field will affect the readings of this sensor. The Compass can return heading data, 
  accelerometer data and magnetometer data on the x, y and z axis.
  
  This example will calibrate the accelerometer. First the X and Y axis are calibrated while 
  the Compass Sensor lays flat. Then the sensor must be placed vertical to calibrate the Z 
  axis. The accelerometer sensitivity can be adjusted. For more information refer to the 
  example Accelerometer_Scale. 
  
  ***The sensor must point due North for the duration of calibration.***
        
  Connections:   
  Compass(default addr 0x24 *0x12*)  = Port I2C
  Touch Sensor(TOUCH)                = Port D7
  *Arduino Address*
    
  NOTE* When using any Core sensor and its accompanying library, the pinMode() function
  should never be used as some sensors change or hold the mode as input/output at 
  certain times to function correctly. All mode initializations are automatically done 
  when the sensor constructor is called. i.e. CORE_TOUCH().

  Modified by Ning on 3/11/2019 for the use of Matrix Mini Controller
-------------------------------------------------------------------------------------------*/
#include "MatrixMini.h"
#include "utility/MiniSerial.h"
MatrixMini Mini;
MiniCoreCompass CompassSensor;

void setup(){
  Mini.begin();
  CompassSensor.begin();
  Serial.begin(9600);

  Mini.LED1.setRGB(200,200,200);
  // Calibrate Accelerometer on X,Y,Z axis inside Compass sensor
  Serial.println("Accelerometer Calibration");
  Serial.println("  1. For X and Y keep sensor perfectly flat. For Z place sensor vertical");
  Serial.println("    Push Mini Button 1 to calibrate X and Y axis");
  while(!Mini.BTN1.get());
  CompassSensor.nullAccX();
  CompassSensor.nullAccY();
  
  Serial.println("  2. Set Compass Vertical for Z axis");
  Serial.println("    Push Mini Button 1 to calibrate Z axis");
  while(!Mini.BTN1.get());
  CompassSensor.nullAccZ();
  Serial.println("*Accelerometer Calibration Complete*"); 
}

void loop(){
}
