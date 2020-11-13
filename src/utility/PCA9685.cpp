#include "PCA9685.h"



void init_PCA9685(uint8_t freq){
    i2cWriteData(ADDR_PCA9685, PCA9685_MODE1, 0x10);
    i2cWriteData(ADDR_PCA9685, PCA9685_PRESCALER, freq);
    i2cWriteData(ADDR_PCA9685, PCA9685_MODE1, 0xA1);
    setPWM_PCA9685(61, 0 , 0); 
}    


void setPWM_PCA9685(uint8_t ch, uint16_t start, uint16_t end){
    Wire.beginTransmission(ADDR_PCA9685);
    Wire.write(PCA9685_PWM0_ON_L + 4*ch);

    start = PWM_overflow_check(start);
    end = PWM_overflow_check(end);

    Wire.write(start);
    Wire.write(start>>8);
    Wire.write(end);
    Wire.write(end>>8);

    Wire.endTransmission();
}

void setPWM_PCA9685(uint8_t ch, uint16_t duty){
    Wire.beginTransmission(ADDR_PCA9685);
    Wire.write(PCA9685_PWM0_ON_L + 4*ch);

    duty = PWM_overflow_check(duty);

    Wire.write(0);
    Wire.write(0);
    Wire.write(duty);
    Wire.write(duty>>8);

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