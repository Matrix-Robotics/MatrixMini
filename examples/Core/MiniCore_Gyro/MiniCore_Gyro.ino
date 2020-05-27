#include "MatrixMini.h"

MatrixMini Mini;
MiniCoreGyro GyroSensor; //Intergrated Gyro Sensor

int RawX,RawY,RawZ;
int Degree;

void setup() {
  Mini.begin();
  GyroSensor.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Interrupt Gyro Compass Sensor Test \n");
  Serial.println(GyroSensor.getVersion(), HEX);
  Serial.println(GyroSensor.getManufacturer());
  Serial.println(GyroSensor.getID(), HEX);
  Serial.println("Reseting Gyro Value...");
  GyroSensor.resetGyro();
  Serial.print("Degrees: ");
  GyroSensor.getDegree(Degree);
  Serial.println(Degree);
  Serial.println("\n < Setup done > \n");
  delay(2000);
}

void loop() {
  GyroSensor.getRawXYZ(RawX, RawY, RawZ);
  GyroSensor.getDegree(Degree);
  Serial.print("Gyro Raw Data: ");
  Serial.print(" Degrees: ");    Serial.print(Degree);
  Serial.print(" X: ");         Serial.print(RawX);
  Serial.print(" Y: ");         Serial.print(RawY);
  Serial.print(" Z: ");         Serial.print(RawZ);
  Serial.println();
  delay(100);
}

