#include <MatrixMini.h>

MatrixMini Mini;


void setup() {
  Mini.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("\n Matrix Mini Ultrasonic Sensor Test \n");
}
//US1, US2, US3, US4
// D1,  D2,  D3,  D4

void loop() {
  Serial.println(Mini.US1.get());
  delay(1000);
}
