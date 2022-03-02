#include <MatrixMini.h>

int dis;

void setup() {
  Mini.begin();
  Serial.begin(115200);  
}

void loop() {
  Serial.println("===============================================================");

  dis = Mini.I2C1.MXlaser.getDistance();

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
