
#include "src/MatrixMini.h"
#include <Arduino.h>
  
uint32_t vccc;
void setup()

{

  Serial.begin(115200);

  Mini.begin();

 // Mini.ENCO.Init(1,3);
}


void loop()

{
 // vccc = Mini.I2C1.HTC.get(RED);
  
  //vccc = float(analogRead(A3));
 // Mini.RGB1.setRGB(vccc >> 16, vccc >> 8, vccc);
 
  Serial.println(Mini.BTN2.get());

  // Serial.print("L: ");

  // Serial.println(Mini.ENCO.get_Angle(L));

  // Serial.println(Mini.ENCO.get_Turn(L));

  // Serial.println(Mini.ENCO.get_Distance(L));

  // Serial.print("R: ");

  // Serial.println(Mini.ENCO.get_Angle(R));

  // Serial.println(Mini.ENCO.get_Turn(R));

  // Serial.println(Mini.ENCO.get_Distance(R));
  //delay(500);

   
  //Mini.RGB2.setRGB(0, 100, 0);

  delay(500);

}
