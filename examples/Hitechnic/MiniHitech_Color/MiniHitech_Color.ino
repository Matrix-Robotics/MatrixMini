#include "MatrixMini.h"

MatrixMini Mini;
MiniHitechColor ColorSensor;

byte r,g,b,grayscale;

void setup() {
  Mini.begin();
  ColorSensor.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Hitech Color Sensor Test \n");
  Serial.println(ColorSensor.getVersion());
  Serial.println(ColorSensor.getManufacturer());
  Serial.println(ColorSensor.getType());
  Serial.println("\n < Setup done > \n");
  delay(2000);
}



void loop() {
  ColorSensor.getRGB(r, g, b);
  
  Serial.print("Color: ");      Serial.print(ColorSensor.getColor());
  Serial.print(" Grayscale: "); Serial.print(ColorSensor.getGrayscale());
  Serial.print(" R: ");         Serial.print(r);
  Serial.print(" G: ");         Serial.print(g);
  Serial.print(" B: ");         Serial.println(b);
  Serial.println();
}

