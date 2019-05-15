#include "MatrixMini.h"

MatrixMini Mini;
MiniHitechIRSeeker IRSeeker;

byte Direction,d1,d2,d3,d4,d5;

void setup() {
  Mini.begin();
  IRSeeker.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Hitech IR Seeker Sensor Test \n");
  Serial.println(IRSeeker.getVersion());
  Serial.println(IRSeeker.getManufacturer());
  Serial.println(IRSeeker.getType());
  Serial.println("\n < Setup done > \n");
  delay(2000);
}

void loop() {
  Direction = IRSeeker.getDirection();
  IRSeeker.getStrength(d1,d2,d3,d4,d5);
  Serial.print("Direction: ");      Serial.print(Direction);
  Serial.print(" Strength: ");
  Serial.print(" d1: ");         Serial.print(d1);
  Serial.print(" d2: ");         Serial.print(d2);
  Serial.print(" d3: ");         Serial.println(d3);
  Serial.print(" d4: ");         Serial.print(d4);
  Serial.print(" d5: ");         Serial.println(d5);
  Serial.println();
}

