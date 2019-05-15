#include <MatrixMini.h>

MatrixMini Mini;


void setup() {
  Mini.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps

  Serial.println("\n Matrix Mini DC Motor Test \n");
  
  // Range 0 to 180 deg
  Mini.RC1.set(0);
  Mini.RC4.set(0);
}


void loop() {
  int i;
  Serial.println("One way");
  for (i=0; i<180; i++) {
    Mini.RC1.set(i); 
    Mini.RC4.set(i); 
    delay(15);
  }
  Serial.println("Or another");
  for (i=180; i>0; i--) {
    Mini.RC1.set(i);  
    Mini.RC4.set(i); 
    delay(15);
  }
}
