#include "PCA9685.h"

void init_PCA9685(uint8_t freq){
    i2cWriteData(ADDR_PCA9685, PCA9685_MODE1, 0x10); // reset driver ic
    i2cWriteData(ADDR_PCA9685, PCA9685_PRESCALER, freq); // set the driver frequncy
    i2cWriteData(ADDR_PCA9685, PCA9685_MODE1, 0xA1); // enable the driver
    setPWM_PCA9685(61, 0);  // set all channel to 0
}    

void setPWM_PCA9685(uint8_t ch, uint16_t duty){
    duty = PWM_overflow_check(duty);

    Wire.beginTransmission(ADDR_PCA9685);
    Wire.write(PCA9685_PWM0_ON_L + 4*ch);

    Wire.write(0);
    Wire.write(0);
    Wire.write(duty);
    Wire.write(duty>>8);

    Wire.endTransmission();
}

void setPWM_PCA9685(uint8_t ch, uint16_t duty1, uint16_t duty2){
    duty1 = PWM_overflow_check(duty1);
    duty2 = PWM_overflow_check(duty2);

    Wire.beginTransmission(ADDR_PCA9685);
    Wire.write(PCA9685_PWM0_ON_L + 4*ch);

    Wire.write(0);
    Wire.write(0);
    Wire.write(duty1);
    Wire.write(duty1>>8);
    Wire.write(0);
    Wire.write(0);
    Wire.write(duty2);
    Wire.write(duty2>>8);

    Wire.endTransmission();
}

void setPWM_PCA9685(uint8_t ch, uint16_t duty1, uint16_t duty2, uint16_t duty3){
    duty1 = PWM_overflow_check(duty1);
    duty2 = PWM_overflow_check(duty2);
    duty3 = PWM_overflow_check(duty3);

    Wire.beginTransmission(ADDR_PCA9685);
    Wire.write(PCA9685_PWM0_ON_L + 4*ch);

    Wire.write(0);
    Wire.write(0);
    Wire.write(duty1);
    Wire.write(duty1>>8);
    Wire.write(0);
    Wire.write(0);
    Wire.write(duty2);
    Wire.write(duty2>>8);
    Wire.write(0);
    Wire.write(0);
    Wire.write(duty3);
    Wire.write(duty3>>8);

    Wire.endTransmission();
}

uint16_t PWM_overflow_check(int pwm){
    if(pwm > 4095){
        return 4095;
    }
    else if(pwm < 0){
        return 0;
    }
    else{
        return pwm;
    }
}