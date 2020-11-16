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

void setup() {
  Mini.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("\nMatrix Mini Test - Ultrasonic Sensor\n");
}
// We suggest you connect Ultrasonic Sensor on digital port

void loop() {
  Serial.print("Distance read from Ultrasonic Sensor at D4 Port: "); 
  Serial.print(Mini.D4.US.get());
  Serial.println("cm");
  delay(1000);
}
