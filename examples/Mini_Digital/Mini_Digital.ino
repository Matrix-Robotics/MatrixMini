#include "MatrixMini.h"

MatrixMini Mini;

void setup() {
  Mini.begin();
  Serial.begin(9600);
  Serial.println("\nMATRIX Mini Test - Digital Read/ Set\n");
  Serial.println("Starting Up ... ");
}

void loop() {
  Serial.print("D1 Port Read: ");  Serial.println(Mini.D1.get());
  Serial.print("D2 Port Read: ");  Serial.println(Mini.D2.get());
  Serial.println("---");
  Mini.D3.set(0);
  Mini.D4.set(0);
  delay(500);
  Mini.D3.set(1);
  Mini.D4.set(1);
  delay(500);
}
