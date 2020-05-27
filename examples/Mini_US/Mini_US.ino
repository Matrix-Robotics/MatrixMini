/*******************
  Mini Ultrasonic Sensor Example
 * Description: Demonstrates how to use Ultrasonic Sensor to
 *              measure the distance between the obstacle and the sensor.
 *
 * Author:      Frason Fan
 * modified 16 Dec 2019
 *  
 * www.matrixrobotics.com
 */
#include <MatrixMini.h>

MatrixMini Mini;


void setup() {
  Mini.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("\nMatrix Mini Test - Ultrasonic Sensor\n");
}
//US1, US2, US3, US4
// D1,  D2,  D3,  D4

void loop() {
  Serial.print("Distance read from Ultrasonic Sensor at D4 Port: "); 
  Serial.print(Mini.US4.get());
  Serial.println("cm");
  delay(1000);
}
