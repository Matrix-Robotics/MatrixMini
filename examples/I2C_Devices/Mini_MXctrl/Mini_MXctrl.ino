/*******************
  Mini Matrix Controller Example
   Description: Demonstrates how to use Matrix Controller with extra motors.

   Author:      Frason Fan
   modified 20 Apr 2021

   www.matrixrobotics.com
*/
#include <MatrixMini.h>

void setup() {
  Mini.begin();
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("\nMatrix Mini Test - Matrix Controller\n");
  Serial.println("Matrix Controller on I2C port 1 ");

  Mini.I2C1.MXctrl.motorInvert(2, true);
  //  MotorInvert Function makes the motor rotate in opposite direction
}

void loop() {
  Serial.print("Motor 1 speed 20");
  Serial.print("Motor 2 speed 20");
  Mini.I2C1.MXctrl.motorSet(1, 20);
  Mini.I2C1.MXctrl.motorSet(2, 20);
  //  MotorSet Function alllows you to set the speed of the motor 1 to motor 4
  //  The value of speed can be asigned from -100 to 100
  delay(1000);

  Serial.print("Motor 1 speed 0");
  Serial.print("Motor 2 speed 0");
  Mini.I2C1.MXctrl.motorSet(1, 0);
  Mini.I2C1.MXctrl.motorSet(2, 0);
  delay(1000);

  Mini.I2C1.MXctrl.motorRound(1, 4);
  Mini.I2C1.MXctrl.motorRound(2, 4);
  //  MotorRound Function can set the number of rounds for the motor to reach

  Mini.I2C1.MXctrl.servoSet(1,180);
  delay(1000);
  Mini.I2C1.MXctrl.servoSet(1,0);
  delay(1000);
  //  ServoSet Function can set the angle for servo motors

  delay(500);
}
