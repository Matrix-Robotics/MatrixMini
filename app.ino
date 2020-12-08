
#include "src/MatrixMini.h"
#include <Arduino.h>
  
#define REG_ENABLE           0x00              // enable register
#define REG_ATIME            0x01              // timing register
#define REG_WTIME            0x03              // wait time  register
#define REG_CONFIG           0x0D              // configuration register
#define REG_CONTROL          0x0F              // controll register
#define REG_ID               0x12              // ID register (constant value 0x44)
#define REG_STATUS           0x13              // ID register (constant value 0x44)
#define REG_CDATAL           0x14              // clear component (low byte)
#define REG_CDATAH           0x15              // clear component (high byte)
#define REG_RDATAL           0x16              // red component (low byte)
#define REG_RDATAH           0x17              // red component (high byte)
#define REG_GDATAL           0x18              // green component (low byte)
#define REG_GDATAH           0x19              // green component (high byte)
#define REG_BDATAL           0x1A              // blue component (low byte)
#define REG_BDATAH           0x1B              // blue component (high byte)

#define SLAVE_ADDRESS        0x29               // color sensor I2C address
#define COMMAND_HEADER       0x80               // bit 7 must be 1 when writing commands

void setup(){
  
  Serial.begin(115200);
  
  
  Mini.begin(LI_2);
  //i2cMUXSelect(3, 3);
  //Color_init();
}
float coff[3][3] ={0.0484, 0.1836, -0.2536, 0.0229, 0.1764, -0.1832, -0.0774, 0.1245, 0.0321};



void loop(){
  
  //Mini.RGB1.setRGB(rr, gg, bb);
  //triggerColorSensor(Color_read(REG_RDATAL), Color_read(REG_GDATAL), Color_read(REG_BDATAL), Color_read(REG_CDATAL));
  //triggerColorSensor(Mini.I2C1.MC.get(RED), Mini.I2C1.MC.get(GREEN), Mini.I2C1.MC.get(BLUE), Mini.I2C1.MC.get(WHITE));
  //vell(30000,30000,30000);

  // Mini.RGB2.setRGB(lego(0x43), lego(0x44), lego(0x45));
  // Serial.println("LEGO------------------------------------");
  // Serial.print("R = ");
  // Serial.println(lego(0x43));
  // Serial.print("G = ");
  // Serial.println(lego(0x44));
  // Serial.print("B = ");
  // Serial.println(lego(0x45));

  // delay(500);
//
//Mini.RGB2.setRGB(map(Mini.I2C1.MC.get(RED), 0, 65535, 0, 255), map(Mini.I2C1.MC.get(GREEN), 0, 65535, 0, 255), map(Mini.I2C1.MC.get(BLUE), 0, 65535, 0, 255));
//delay(300);


  Mini.RC1.set(90);
  Mini.RC2.set(90);
  Mini.RC3.set(90);
  Mini.RC4.set(90);

  // Serial.println("=================");
  // i2cWriteData(0x22, 0x56);
  // buff= i2cReadData(0x22, 2);
  // Serial.println(buff);
  // Serial.print("L turn: "); Serial.println(Mini.ENCO.get_Turn(L));
  // Serial.print("L angle: "); Serial.println(Mini.ENCO.get_Angle(L));
  // Serial.print("L D: ");   Serial.println(Mini.ENCO.get_Distance(L));
  // Serial.println("");
  // Serial.print("R turn: ");  Serial.println(Mini.ENCO.get_Turn(R));
  // Serial.print("R angle: ");  Serial.println(Mini.ENCO.get_Angle(R));
  // Serial.print("R D: ");  Serial.println(Mini.ENCO.get_Distance(R));
  //delay(500);
 
   
  //Mini.RGB2.setRGB(0, 100, 0);

  

}

uint8_t lego(int color){
  i2cMUXSelect(2, 3);
  return i2cReadData(0x01, color, 1);
}

void triggerColorSensor(uint16_t _r, uint16_t _g, uint16_t _b, uint16_t _w)
{
  
  float red, green,blue, max, min, h, s, v, delta;
  float f,p,q,t;
  uint8_t data8,i;
  
  Serial.println("Origin------------------------------------");
  Serial.print("R = ");
  Serial.println(_r);
  Serial.print("G = ");
  Serial.println(_g);
  Serial.print("B = ");
  Serial.println(_b);

  
  //**********************************************************
  // convert raw data into RGB (0~1)
  //**********************************************************    
  red   = (float)_r / (float)_w;
  green = (float)_g / (float)_w;  
  blue  = (float)_b / (float)_w;  
  


  //**********************************************************
  // convert RGB into HSV
  //********************************************************** 
  if( ( red   > green ) && ( red   > blue ) ) max = red;
  if( ( green > red   ) && ( green > blue ) ) max = green;
  if( ( blue  > red   ) && ( blue  > green) ) max = blue;
  v = max;
  
  if( ( red   < green ) && ( red   < blue ) ) min = red;
  if( ( green < red   ) && ( green < blue ) ) min = green;
  if( ( blue  < red   ) && ( blue  < green) ) min = blue;
  
  
  delta = max - min;
  s = delta/max;
  
  if( red == max )        h =     ( green - blue ) / delta;
  else if( green == max ) h = 2 + ( blue - red )   / delta;
  else                    h = 4 + ( red - green )  / delta;
  
  h = h * 60;
  if( h < 0 ) h = h + 360;
  
  
  //**********************************************************
  // storing RGB and HSV
  //********************************************************** 
  float componentRed   = red   * 255;
  float componentGreen = green * 255;
  float componentBlue  = blue  * 255;
  
  Serial.println("Pre------------------------------------");
  Serial.print("R = ");
  Serial.println((uint8_t) componentRed);
  Serial.print("G = ");
  Serial.println((uint8_t) componentGreen);
  Serial.print("B = ");
  Serial.println((uint8_t) componentBlue);

  //setPWM_PCA9685(3, map((uint8_t) componentRed, 0, 255, 0, 4095), map((uint8_t) componentGreen, 0, 255, 0, 4095), map((uint8_t) componentBlue, 0, 255, 0, 4095));


  float componentHue = h;
  float componentSaturation = s;
  float componentValue = v;   
  
  //**********************************************************
  //adjust saturation and value, hue remains unchanged
  //**********************************************************   
  v = 1.0;
  s = 1.0;

  componentHue = h;
  componentSaturation = s;
  componentValue = v;  
    
  //**********************************************************
  //convert back to RGB
  //********************************************************** 

  h = h / 60;
  i = floor(h);

  f = h - i;			
  p = v * ( 1 - s );
  q = v * ( 1 - s * f );
  t = v * ( 1 - s * ( 1 - f ) );
  
  switch( i )
  {
    case 0: 
    red = v; green = t; blue = p;
      break;
    case 1:
      red = q; green = v; blue = p;
      break;
    case 2:
      red = p; green = v; blue = t;
      break;
    case 3:
      red = p; green = q; blue = v;
      break;
    case 4:
      red = t; green = p; blue = v;
      break;
    default:                        // case 5:
      red = v; green = p; blue = q;
      break;
  }


  //**********************************************************
  //scale RGB data 0~255 
  //**********************************************************  
  componentRed   = red   * 255;
  componentGreen = green * 255;
  componentBlue  = blue  * 255;
  


  Serial.println("Adj------------------------------------");
  Serial.print("R = ");
  Serial.println((uint8_t) componentRed);
  Serial.print("G = ");
  Serial.println((uint8_t) componentGreen);
  Serial.print("B = ");
  Serial.println((uint8_t) componentBlue);

  
  setPWM_PCA9685(0, map((uint8_t) componentRed, 0, 255, 0, 4095), map((uint8_t) componentGreen, 0, 255, 0, 4095), map((uint8_t) componentBlue, 0, 255, 0, 4095));

}



void Color_init()
{
  i2cWriteData(SLAVE_ADDRESS, COMMAND_HEADER | REG_ENABLE, 0x01);     // power on  
  delayMicroseconds(10);

  //write(REG_ATIME, 0xF6);      // set integration time 24 ms
  i2cWriteData(SLAVE_ADDRESS, COMMAND_HEADER | REG_ATIME, 0xC0);      // set integration time 154 ms
  i2cWriteData(SLAVE_ADDRESS, COMMAND_HEADER | REG_CONFIG, 0x00);     // no long wait time
  //write(REG_CONTROL, 0x00);    // set 1 x gain 
  i2cWriteData(SLAVE_ADDRESS, COMMAND_HEADER | REG_CONTROL, 0x02);    // set 16 x gain 
  i2cWriteData(SLAVE_ADDRESS, COMMAND_HEADER | REG_ENABLE, 0x03);     // power on and activate color capturing  
}

uint16_t Color_read(uint8_t register_address)
{
  i2cMUXSelect(3, 3);
  uint16_t dataL, dataH, data;
	
  Wire.beginTransmission(SLAVE_ADDRESS);                 // slave address
  Wire.write(COMMAND_HEADER | register_address);         // command header + register address
  Wire.endTransmission(); 
  Wire.requestFrom(SLAVE_ADDRESS, 2);                    // request two bytes of data
  dataL = Wire.read();                                   // received lowest 8 bits of data
  dataH = Wire.read();                                   // received highest 8 bits of data
  data = (dataH << 8) | dataL;                           // combine lowest and highest bits

   return data ;
}




void vell(uint16_t _r, uint16_t _g, uint16_t _b){
  int i;
  int j;
  float clr[3]= {_r, _g, _b};
  float m[3]={0, 0, 0};
  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      m[i] += int((coff[i][j])*(clr[j]));
    }
  }
  //Mini.RGB2.setRGB((m[0], m[1], m[2]);
  setPWM_PCA9685(0, map(m[0], 0, 1023, 0, 4095), map(m[1], 0, 1023, 0, 4095), map(m[2], 0, 1023, 0, 4095));
  Serial.println("Origin------------------------------------");
  Serial.print("R = ");
  Serial.println(_r);
  Serial.print("G = ");
  Serial.println(_g);
  Serial.print("B = ");
  Serial.println(_b);

  

  Serial.println("MATRIX------------------------------------");
  Serial.print("R = ");
  Serial.println(m[0]);
  Serial.print("G = ");
  Serial.println(m[1]);
  Serial.print("B = ");
  Serial.println(m[2]);

  // float mm = (m[0]+m[1]+m[2])/100;

  // Serial.println("MATRIX %------------------------------------");
  // Serial.print("R = ");
  // Serial.println(m[0]/mm);
  // Serial.print("G = ");
  // Serial.println(m[1]/mm);
  // Serial.print("B = ");
  // Serial.println(m[2]/mm);


}