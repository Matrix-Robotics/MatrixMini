/*
  Matrix Mini Library Test

 * Lib: v2.4.5 or newer
 * Author: Barry
 * Modified: 26 Jan 2025

  www.matrixrobotics.com
*/
#include <MatrixMini.h>

void setup() {
  bool ret = Mini.begin();
  Serial.begin(115200);

  Mini.M1.set(0);
  Mini.M2.set(0);

  Mini.RC1.set(0);
  Mini.RC2.set(0);
  Mini.RC3.set(0);
  Mini.RC4.set(0);

  Mini.RGB1.setRGB( 0, 0, 0);
  Mini.RGB2.setRGB( 0, 0, 0);

  if (ret) {
    Serial.println("Matrix Mini init success");
  } else {
    Serial.println("Matrix Mini init failed");
  }

  delay(1000);
}

void loop() {
  // TaskLED();
  // TaskButton();
  // TaskDCMotor();
  // TaskServoMotor();
  // TaskDigital();
  // TaskAnalog();
  // TaskUS();  // D4
  // TaskHTColor();   // I2C1
  // TaskHTCompass(); // I2C2
  // TaskMXColor();   // I2C3
  // TaskMXLaser();   // I2C4
  // TaskMXCtrl();    // I2C1
  // TaskMJ2();
  
}

void TaskLED() {
  Mini.RGB1.setRGB( 255, 0, 0);
  Mini.RGB2.setRGB( 255, 0, 0);
  delay(500);
  Mini.RGB1.setRGB( 0, 255, 0);
  Mini.RGB2.setRGB( 0, 255, 0);
  delay(500);
  Mini.RGB1.setRGB( 0, 0, 255);
  Mini.RGB2.setRGB( 0, 0, 255);
  delay(500);
}

void TaskButton() {
  bool BTN1 = Mini.BTN1.get();
  bool BTN2 = Mini.BTN2.get();

  Serial.print("BTN1: ");
  Serial.print(BTN1);
  Serial.print(", BTN1: ");
  Serial.println(BTN2);
  delay(100);
}

void TaskDCMotor() {
  int i;
  
  Serial.println("One way");
  for (i=0; i<100; i++) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  for (i=100; i>0; i--) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  delay(500);
  Serial.println("Or another");
  for (i=0; i>-100; i--) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  for (i=-100; i<0; i++) {
    Mini.M1.set(i);  
    Mini.M2.set(i);
    delay(15);
  }
  delay(500);
}

void TaskServoMotor() {
  int i;
  Serial.println("One way");
  Mini.RC1.set(0);
  Mini.RC2.set(0);
  for (i = 0; i < 180; i++) {
    Mini.RC3.set(i); 
    Mini.RC4.set(i); 
    delay(10);
  }
  delay(500);
  Mini.RC1.set(180);
  Mini.RC2.set(180);
  Serial.println("Or another");
  for (i = 180; i > 0; i--) {
    Mini.RC3.set(i);  
    Mini.RC4.set(i); 
    delay(10);
  }
  delay(500);
}

void TaskDigital() {
  Serial.print("D1 Port Read: ");  Serial.println(Mini.D1.get());
  Serial.print("D2 Port Read: ");  Serial.println(Mini.D2.get());
  Serial.println("---");
  Serial.print("D3 Port Set: 0");  
  Serial.println("D4 Port Set: 0");
  Serial.println("---");
  Mini.D3.set(0);
  Mini.D4.set(0);
  delay(500);  
  Serial.print("D3 Port Set: 1");  
  Serial.println("D4 Port Set: 1");
  Serial.println("---");
  Mini.D3.set(1);
  Mini.D4.set(1);
  delay(500);
}

void TaskAnalog() {
  Serial.print("A1 Port Read: ");  Serial.println(Mini.A1.getANG());
  Serial.print("A3 Port Read: ");  Serial.println(Mini.A3.getANG());
  Serial.println("---");
  delay(2000);
}

void TaskUS() {
  Serial.print("Distance read from Ultrasonic Sensor at D4 Port: "); 
  Serial.print(Mini.D4.US.get());
  Serial.println("cm");
  delay(1000);
}
void TaskHTColor() {
  Serial.print("Get Red : ");
  Serial.println(Mini.I2C1.HTcolor.getR());
  Serial.print("Get Green : ");
  Serial.println(Mini.I2C1.HTcolor.getG());
  Serial.print("Get Blue : ");
  Serial.println(Mini.I2C1.HTcolor.getB());

  Serial.println("=================");
  Serial.print("Get Color Number : ");
  Serial.println(Mini.I2C1.HTcolor.getColorNumber());
  Serial.println("=================");
  Serial.print("Get Grayscale : ");
  Serial.println(Mini.I2C1.HTcolor.getGrayscale());
  Serial.println("=================");

  delay(500);
}

void TaskHTCompass() {
  Serial.print("Get Red : ");
  Serial.println(Mini.I2C2.HTcompass.getHeading());
  //  Get Heading Function returns a number from 0 to 359
  Serial.println("=================");

  delay(500);
}

void TaskMXColor() {
  while (true) {
    int r = Mini.I2C3.MXcolor.getColor(R);
    int g = Mini.I2C3.MXcolor.getColor(G);
    int b = Mini.I2C3.MXcolor.getColor(B);
    int c = Mini.I2C3.MXcolor.getColor(C);
    int m = Mini.I2C3.MXcolor.getColor(M);
    int y = Mini.I2C3.MXcolor.getColor(Y);
    int k = Mini.I2C3.MXcolor.getColor(K);

    char buff[64];
    sprintf(buff, "R: %3d, G: %3d, B: %3d, C: %3d, M: %3d, Y: %3d, K: %3d\n", r, g, b, c, m, y, k);
    Serial.print(buff);

    delay(100);
  }
}

void TaskMXLaser() {
  dis = Mini.I2C4.MXlaser.getDistance();

  if(dis == 8191){
    Serial.println("TIMEOUT");
  }
  else{
    Serial.print("Distance = ");
    Serial.print(dis);
    Serial.println("mm");
  }
  delay(100);
}

void TaskMXCtrl() {
  Mini.I2C1.MXCtrl.motorInvert(1, false);  // Set Direction

  Mini.I2C1.MXCtrl.servoSet(1, 0);   // Servo Motor
  Mini.I2C1.MXCtrl.motorSet(1, 60);  // Large DC Motor
  delay(1000);

  Mini.I2C1.MXCtrl.servoSet(1, 90);
  Mini.I2C1.MXCtrl.motorSet(1, 0);
  delay(500);
}

void TaskMJ2() {
  Mini.PS2.polling();

  int LY = Mini.PS2.LY;
  int RX = Mini.PS2.RX;

  Serial.print("LY: ");
  Serial.print(LY);
  Serial.print(", RX: ");
  Serial.println(RX);

  delay(10);
}