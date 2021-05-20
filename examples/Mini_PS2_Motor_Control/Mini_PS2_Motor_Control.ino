/*******************
  Mini PS2 Controller Example
   Description: Demonstrates how to control motors with joysticks on PS2 Controller


   Author:      Frason Fan
   modified 20 May 2021

   www.matrixrobotics.com
*/
#include <MatrixMini.h>

void setup() {
  Mini.begin();
  Serial.begin(115200);
  if (Mini.PS2.begin()) { // 4 Wires on D1, 2 Wires on D3
    Serial.println("PS2 controller detect!");
  }
  else {
    Serial.println("could not find PS2 controller");
    Serial.println("make sure your controller power is on and press the start button");
    while (1);
  }
}

void loop() {
  delay(50);
  Mini.PS2.polling(); // Get values every loop

  int throttle = map(Mini.PS2.LY, 0, 256, -100, 100);
  int steering = map(Mini.PS2.RX, 0, 256, -40, 40);

  Mini.M1.set(constrain(throttle - steering, -100, 100));
  Mini.M2.set(constrain(throttle + steering, -100, 100));

}
