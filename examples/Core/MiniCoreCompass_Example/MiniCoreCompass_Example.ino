#include "MatrixMini.h"

MatrixMini Mini;
MiniCoreCompass CompassSensor;

int AccX,AccY,AccZ;
int MagX,MagY,MagZ;

void setup() {
  Mini.begin();
  CompassSensor.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Core Compass Sensor Test \n");
  Serial.println(CompassSensor.getVersion(), HEX);
  Serial.println(CompassSensor.getManufacturer());
  Serial.println(CompassSensor.getID(), HEX);
  Serial.println("\n < Setup done > \n");
  delay(2000);
}

void loop() {
  CompassSensor.getAccXYZ(AccX, AccY, AccZ);
  CompassSensor.getMagXYZ(MagX, MagY, MagZ);
  //Serial.print("Color: ");      Serial.print(CompassSensor.getColor());
  //Serial.print(" Grayscale: "); Serial.print(CompassSensor.getGrayscale());
  Serial.print("Accelerometer: ");
  Serial.print(" X: ");         Serial.print(AccX);
  Serial.print(" Y: ");         Serial.print(AccY);
  Serial.print(" Z: ");         Serial.println(AccZ);
  Serial.print(" Magnetometer: ");
  Serial.print(" X: ");         Serial.print(MagX);
  Serial.print(" Y: ");         Serial.print(MagY);
  Serial.print(" Z: ");         Serial.println(MagZ);
  Serial.println();
}

