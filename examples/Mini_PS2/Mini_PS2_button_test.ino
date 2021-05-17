/*******************
  Mini Ultrasonic Sensor Example
 * Description: Demonstrates how to use Ultrasonic Sensor to
 *              measure the distance between the obstacle and the sensor.
 *
 * Author:      Roger Chen
 * modified 17 May 2021
 *  
 * www.matrixrobotics.com
 */
#include "src/MatrixMini.h"
#include <arduino.h>


void setup() {
    Mini.begin();
    Serial.begin(115200);
    if(Mini.PS2.begin()){ // 4 Wires on D1, 2 Wires on D3
        Serial.println("PS2 controller detect!");
    }
    else{
        Serial.println("could not find PS2 controller");
        Serial.println("make sure your controller power is on and press the start button");
        while(1);
    }
}

void loop() {
    delay(50);
    Mini.PS2.polling();
    Serial.println("  ===========                             ===========  ");
    Serial.println(" =     "+(String)(Mini.PS2.L2)+"     =                           =     "
    +(String)(Mini.PS2.R2)+"     = ");
    Serial.println("=      "+(String)(Mini.PS2.L1)+"      =                         =      "
    +(String)(Mini.PS2.R1)+"      = ");
    Serial.println("=              =========================              =");
    Serial.println("=                                                     =");
    Serial.println("=      "+(String)(Mini.PS2.UP)+"                                       "
    +(String)(Mini.PS2.TRIANGLE)+"      =");
    Serial.println("=    "+(String)(Mini.PS2.LEFT)+"   "+(String)(Mini.PS2.RIGHT)+"          "
    +(String)(Mini.PS2.SELECT)+"             "+(String)(Mini.PS2.START)+"          "+(String)(Mini.PS2.SQUARE)
    +"   "+(String)(Mini.PS2.CIRCLE)+"    =");
    Serial.println("=      "+(String)(Mini.PS2.DOWN)+"                                       "
    +(String)(Mini.PS2.X)+"      =");
    Serial.println("=                                                     =");
    Serial.println("=          X = "+(String)(Mini.PS2.LX)+"                   X = "
    +(String)(Mini.PS2.RX)+"          =");
    Serial.println("=          Y = "+(String)(Mini.PS2.LY)+"                   Y = "
    +(String)(Mini.PS2.RY)+"          =");
    Serial.println("=         ===================================         =");
    Serial.println("=        =                                   =        =");
    Serial.println("=========                                     =========");
    Serial.println("");
    Serial.println("");
}
