#include <MatrixMini.h>

int channel, angle;

void setup()
{
    Mini.begin();
    Serial.begin(115200);
}

void loop()
{
    Serial.println("===============================================================");
    
    Serial.print("Voltage=");
    Serial.println(Mini.I2C1.MXservo.getVbat()); // unit = V 

    channel = 1;
    angle = 0;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);
    delay(250);

    channel = 2;
    angle = 60;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);
    delay(250);

    channel = 3;
    angle = 120;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);
    delay(250);

    channel = 4;
    angle = 180;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);
    delay(250);

    channel = 5;
    angle = 0;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);
    delay(250);

    channel = 6;
    angle = 60;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);
    delay(250);

    channel = 7;
    angle = 120;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);
    delay(250);

    channel = 8;
    angle = 180;
    Mini.I2C1.MXservo.setAngle(channel, angle);
    Serial.println("set channel " + (String)channel + " to " + (String)angle);

    Mini.I2C1.MXservo.ChannelRelease(channel);
    Serial.println("channel " + (String)channel + " release");

    delay(250);
}