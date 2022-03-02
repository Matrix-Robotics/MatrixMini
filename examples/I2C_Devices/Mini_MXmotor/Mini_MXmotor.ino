#include <MatrixMini.h>

int channel, pwm;

void setup() {
  Mini.begin();
  Serial.begin(115200);  
}

void loop()
{
    Serial.println("===============================================================");
    
    Serial.print("Voltage=");
    Serial.println(Mini.I2C1.MXmotor.getVbat()); // unit = V 

    channel = 1;
    pwm = 255;
    Mini.I2C1.MXmotor.setPWM(channel, pwm);
    Serial.println("set channel " + (String)channel + " to " + (String)pwm);
    delay(500);

    channel = 2;
    pwm = -255;
    Mini.I2C1.MXmotor.setPWM(channel, pwm);
    Serial.println("set channel " + (String)channel + " to " + (String)pwm);
    delay(500);

    channel = 1;
    pwm = -255;
    Mini.I2C1.MXmotor.setPWM(channel, pwm);
    Serial.println("set channel " + (String)channel + " to " + (String)pwm);
    delay(500);

    channel = 2;
    pwm = 255;
    Mini.I2C1.MXmotor.setPWM(channel, pwm);
    Serial.println("set channel " + (String)channel + " to " + (String)pwm);
    delay(500);
}
