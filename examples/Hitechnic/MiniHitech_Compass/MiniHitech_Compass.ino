#include "MatrixMini.h"

MatrixMini Mini;
MiniHitechCompass CompassSensor;

int headings;

void setup() {
  Mini.begin();
  CompassSensor.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Hitech Accel Sensor Test \n");
  Serial.println(CompassSensor.getVersion());
  Serial.println(CompassSensor.getManufacturer());
  Serial.println(CompassSensor.getType());
  Serial.println("\n < Setup done > \n");
  delay(2000);
}



void loop() {
  // Get Value
  headings = CompassSensor.getHeading();

  // Print Value
  Serial.print(" headings: ");    Serial.println(headings);

  // Loop delay
  delay(50);
}
