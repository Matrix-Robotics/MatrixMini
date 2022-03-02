#include <MatrixMini.h>


void setup() {
  Mini.begin();
  Serial.begin(115200);  
}

void loop()
{
    Serial.println("===============================================================");
    // Accel unit: mm/s^2
    Serial.print("ax=");
    Serial.println(Mini.I2C1.MXmotion.getAccel(x));
    Serial.print("ay=");
    Serial.println(Mini.I2C1.MXmotion.getAccel(y));
    Serial.print("az=");
    Serial.println(Mini.I2C1.MXmotion.getAccel(z));

    // Euler Angle unit: Angle (Degree)
    // Roll range -180 to 180
    Serial.print("roll=");
    Serial.println(Mini.I2C1.MXmotion.getRoll());

    // pitch range -90 to 90
    Serial.print("pitch=");
    Serial.println(Mini.I2C1.MXmotion.getPitch());

    // Yaw range -180 to 180
    Serial.print("yaw=");
    Serial.println(Mini.I2C1.MXmotion.getYaw());

    // Gyro unit: degree per second
    Serial.print("gx=");
    Serial.println(Mini.I2C1.MXmotion.getGyro(x));
    Serial.print("gy=");
    Serial.println( Mini.I2C1.MXmotion.getGyro(y));
    Serial.print("gz=");
    Serial.println(Mini.I2C1.MXmotion.getGyro(z));

    delay(250);
}