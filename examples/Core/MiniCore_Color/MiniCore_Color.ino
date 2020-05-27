#include "MatrixMini.h"

MatrixMini Mini;
MiniCoreColor ColorSensor;

byte r,g,b,grayscale;

void setup() {
  Mini.begin();
  ColorSensor.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Core Color Sensor Test \n");
  Serial.println(ColorSensor.getVersion(), HEX);
  Serial.println(ColorSensor.getManufacturer());
  Serial.println(ColorSensor.getID(), HEX);
  Serial.println("\n < Setup done > \n");
  delay(2000);

  // Set the mode and sample rate of the color Sensor to Active (default) or Passive at 60Hz
//  ColorSensor.setActiveMode();
//  ColorSensor.setPassiveMode();
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

