#include "MatrixMini.h"
#include "utility/MiniSerial.h"
MatrixMini Mini;
MiniCoreColor ColorSensor;
MiniCoreGyro GyroSensor;
MiniCoreCompass CompassSensor;
MiniCoreSeeker SeekerSensor;

#define RATE 100
unsigned long int myTimer = 0;
byte incomingByte;

// Core I2C Sensor Variables
byte colorIndex = 0;   //Core Color Sensor
byte colorRGB[3];
// Interrupt Gyro Degrees
int  gyroDegree = 0;
byte gyroBuf[2];
// IR Seeker Value
byte seekerDirection = 0;
byte seekerStrength = 0;
// Compass Value
byte compassAccBuf[6];
byte compassMagBuf[6];
int AccX,AccY,AccZ;
int MagX,MagY,MagZ;

void setup() {
  Mini.begin(); 
  Serial.begin(9600);

  // Initializing Core sensors
  GyroSensor.begin();
  GyroSensor.resetGyro();
}

void loop() {
  if(millis() - myTimer > RATE){
    myTimer = millis();
    Send();
    Receive();
  }
  coreUpdate(); //read Core sensor values
}

// Write Data to Serial
void Send(){
  // Mini onboard values
  sendMessage(BTN1, Mini.BTN1.get());
  sendMessage(BTN2, Mini.BTN2.get());
  sendMessage(D1_STATUS, Mini.D1.get());
  sendMessage(D2_STATUS, Mini.D2.get());
  sendMessage(D3_STATUS, Mini.D3.get());
  sendMessage(D4_STATUS, Mini.D4.get());
  sendMessage(A1_STATUS, map(Mini.ANG1.get(), 0, 1023, 0, 254));
  sendMessage(A2_STATUS, map(Mini.ANG2.get(), 0, 1023, 0, 254));
  sendMessage(A3_STATUS, map(Mini.ANG3.get(), 0, 1023, 0, 254));
  
  //Core I2C Data
  sendMessage(CORE_COLOR_IDX, colorIndex);
  sendMessageBuf(CORE_COLOR_RGB, 3, colorRGB);
  sendMessageBuf(CORE_GYRO_DEG, 2, gyroBuf);
  sendMessage(CORE_SEEKER_DIR, seekerDirection);
  sendMessage(CORE_SEEKER_SIG, seekerStrength);
  sendMessageBuf(CORE_COMPASS_ACC, 6, compassAccBuf);
  sendMessageBuf(CORE_COMPASS_MAG, 6, compassMagBuf);
}

// Read data from Serial
void Receive(){
  while(Serial.available()>0){
        incomingByte = Serial.read();
        if(incomingByte != START_SYSEX) continue;
        while(Serial.available()<2);
        byte field = Serial.read();
        byte value = Serial.read();

        // Compare field and apply value
        if(field== SYSTEM_RST);
        else if(field== M1_CONFIG) Mini.M1.set((int8_t)value);
        else if(field== M2_CONFIG) Mini.M2.set((int8_t)value);
        else if(field== RC1_ANGLE) Mini.RC1.set(value);
        else if(field== RC2_ANGLE) Mini.RC2.set(value);
        else if(field== RC3_ANGLE) Mini.RC3.set(value);
        else if(field== RC4_ANGLE) Mini.RC4.set(value);
        else if(field== LED1_HSV) Mini.LED1.setHSV(map(value, 0, 254, 0, 360), 1.0, 1.0);
        else if(field== LED2_HSV) Mini.LED2.setHSV(map(value, 0, 254, 0, 360), 1.0, 1.0);
        else if(field== BTN1) ;
        else if(field== BTN2) ;
        else if(field== D1_CONFIG) Mini.D1.set(value);
        else if(field== D2_STATUS) Mini.D2.set(value);
        else if(field== D3_CONFIG) Mini.D3.set(value);
        else if(field== D4_CONFIG) Mini.D4.set(value);
        else if(field== A1_STATUS) Mini.ANG1.set(map(value, 0, 254, 0, 1023));
        else if(field== A2_STATUS) Mini.ANG2.set(map(value, 0, 254, 0, 1023));
        else if(field== A3_STATUS) Mini.ANG3.set(map(value, 0, 254, 0, 1023));
        else ;
   }
}

void coreUpdate(){
  ColorSensor.begin();
  ColorSensor.getRGB(colorRGB[0],colorRGB[1],colorRGB[2]);
  colorIndex = ColorSensor.getColor();
  
  GyroSensor.begin();
  GyroSensor.getDegree(gyroDegree);
  gyroBuf[0] = (byte) gyroDegree & 0xFF; //lsb
  gyroBuf[1] = (byte) (gyroDegree >> 8) & 0xFF;    //msb
  
  SeekerSensor.begin();
  seekerDirection = SeekerSensor.directionData();
  seekerStrength = SeekerSensor.signalStrength();
  
  CompassSensor.begin();
  CompassSensor.getAccXYZ(AccX, AccY, AccZ);
  compassAccBuf[0] = (byte) AccX & 0xFF;           //lsb
  compassAccBuf[1] = (byte) (AccX >> 8) & 0xFF;    //msb
  compassAccBuf[2] = (byte) AccY & 0xFF;           //lsb
  compassAccBuf[3] = (byte) (AccY >> 8) & 0xFF;    //msb
  compassAccBuf[4] = (byte) AccZ & 0xFF;           //lsb
  compassAccBuf[5] = (byte) (AccZ >> 8) & 0xFF;    //msb
  CompassSensor.getMagXYZ(MagX, MagY, MagZ);
  compassMagBuf[0] = (byte) MagX & 0xFF;           //lsb
  compassMagBuf[1] = (byte) (MagX >> 8) & 0xFF;    //msb
  compassMagBuf[2] = (byte) MagY & 0xFF;           //lsb
  compassMagBuf[3] = (byte) (MagY >> 8) & 0xFF;    //msb
  compassMagBuf[4] = (byte) MagZ & 0xFF;           //lsb
  compassMagBuf[5] = (byte) (MagZ >> 8) & 0xFF;    //msb
}

