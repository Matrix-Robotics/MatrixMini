#include "MatrixMini.h"

MatrixMini Mini;
MiniHitechAccel AccelSensor;

int x,y,z;

void setup() {
  Mini.begin();
  AccelSensor.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Hitech Accel Sensor Test \n");
  Serial.println(AccelSensor.getVersion());
  Serial.println(AccelSensor.getManufacturer());
  Serial.println(AccelSensor.getType());
  Serial.println("\n < Setup done > \n");
  delay(2000);
}



void loop() {
  // Get Value
  AccelSensor.getXYZ(x, y, z);

  // Print Value
  Serial.print(" X: ");    Serial.print(x);
  Serial.print(" Y: ");    Serial.print(y);
  Serial.print(" Z: ");    Serial.println(z);

  // Loop delay
  delay(10);
}
