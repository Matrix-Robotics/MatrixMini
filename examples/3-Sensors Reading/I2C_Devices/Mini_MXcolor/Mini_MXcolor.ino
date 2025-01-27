#include <MatrixMini.h>

void setup() {
  Mini.begin();
  Serial.begin(115200);
  Mini.I2C1.MXcolor.setGamma(true); // enable gamma correction
  Serial.println("Set gamma correction as open");

  Mini.I2C1.MXcolor.setLight(true, true, 0); // enable fill light, and set in auto mode
  Serial.println("Set fill-light open and in auto adjust mode");
}

void loop() {
  Serial.println("===============================================================");
  Serial.print("R=");
  Serial.println(Mini.I2C1.MXcolor.getColor(R));
  Serial.print("G=");
  Serial.println(Mini.I2C1.MXcolor.getColor(G));
  Serial.print("B=");
  Serial.println(Mini.I2C1.MXcolor.getColor(B));
  Serial.print("C=");
  Serial.println(Mini.I2C1.MXcolor.getColor(C));
  Serial.print("M=");
  Serial.println(Mini.I2C1.MXcolor.getColor(M));
  Serial.print("Y=");
  Serial.println(Mini.I2C1.MXcolor.getColor(Y));
  Serial.print("K=");
  Serial.println(Mini.I2C1.MXcolor.getColor(K));
  Serial.print("grayscale=");
  Serial.println(Mini.I2C1.MXcolor.getGrayscale());
  
  getColorNumber();

  delay(500);
}

void getColorNumber(){
  switch (Mini.I2C1.MXcolor.getColorNumber())
  {
  case 0:
    Serial.println("Black");
    break;
  case 1:
    Serial.println("White");
    break;
  case 2:
    Serial.println("Cyan");
    break;
  case 3:
    Serial.println("Ocean");
    break;
  case 4:
    Serial.println("Blue");
    break;
  case 5:
    Serial.println("Violet");
    break;
  case 6:
    Serial.println("Magenta");
    break;
  case 7:
    Serial.println("Raspberry");
    break;
  case 8:
    Serial.println("Red");
    break;
  case 9:
    Serial.println("Orange");
    break;
  case 10:
    Serial.println("Yellow");
    break;
  case 11:
    Serial.println("Spring Green");
    break;
  case 12:
    Serial.println("Green");
    break;
  case 13:
    Serial.println("Turquoise");
    break;
  
  default:
    break;
  }
}
