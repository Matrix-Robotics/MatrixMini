#include "MatrixMini.h"

MatrixMini Mini;
MiniHitechCtrl MXctrl;

byte tmp;

void setup() {
  Mini.begin();
  MXctrl.begin();
  Serial.begin(9600);

  Serial.println("\n Matrix Mini Hitechnic Matrix Controller Test \n");
  Serial.println("Starting Up ... ");
  Serial.println(MXctrl.getVersion());
  Serial.println(MXctrl.getManufacturer());
  Serial.println(MXctrl.getType());
  Serial.println(MXctrl.getStatus(), BIN);
  Serial.println(MXctrl.getBattery());

  MXctrl.setTimeout(0);

  MXctrl.motorMode(Motor1, MODE_POWER_FLOAT);
  MXctrl.motorMode(Motor2, MODE_POWER_BRAKE);
  MXctrl.motorMode(Motor3, MODE_SPEED);
  MXctrl.motorMode(Motor4, MODE_POSITION);

  Serial.println("\n < Setup done > \n");
  delay(2000);
}


long pos, oldpos;
int8_t i;

void loop() {
  Serial.println("One way");
  for (i=-100; i<100; i++) {
    MXctrl.motorSpeed(Motor1, i);
    MXctrl.motorSpeed(Motor2, i); 
    MXctrl.motorSpeed(Motor3, i); 
    MXctrl.motorTarget(Motor4, i);
    delay(15);
  }
  
  Serial.println("Or another");
  for (i=100; i>-100; i--) {
    MXctrl.motorSpeed(Motor1, i);
    MXctrl.motorSpeed(Motor2, i); 
    MXctrl.motorSpeed(Motor3, i); 
    MXctrl.motorTarget(Motor4, i);
    delay(15);
  }
  
}
