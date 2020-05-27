#include "MatrixMini.h"

MatrixMini Mini;
MiniCoreSeeker SeekerSensor;

void setup() {
  Mini.begin();
  SeekerSensor.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Core Seeker Sensor Test \n");
  Serial.println(SeekerSensor.getVersion(), HEX);
  Serial.println(SeekerSensor.getManufacturer());
  Serial.println(SeekerSensor.getID(), HEX);
  Serial.println("\n < Setup done > \n");
  delay(2000);
}



void loop() {
  //SeekerSensor.directionData(600);
  //SeekerSensor.directionData(1200);
  //SeekerSensor.signalStrength(600);
  //SeekerSensor.signalStrength(1200);
  Serial.print(" DIR: ");    Serial.print(SeekerSensor.directionData());
  Serial.print(" SIG: ");    Serial.print(SeekerSensor.signalStrength());
  Serial.println();
  delay(50);
}
