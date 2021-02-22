#include "PCA9633.h"

void setPWM_PCA9633(uint8_t channel, uint8_t duty){
    duty = PWM_check(duty);

    i2cWriteData(ADDR_PCA9633, PCA9633_PWM0 + channel, duty);
}

void setPWM_PCA9633(uint8_t channel, uint8_t duty1, uint8_t duty2){
    duty1 = PWM_check(duty1);
    duty2 = PWM_check(duty2);

    i2cWriteData(ADDR_PCA9633, PCA9633_PWM0 + channel, duty1, duty2);
}

void init_PCA9633(){
    i2cWriteData(ADDR_PCA9633, PCA9633_MODE1, 0x00); //Turn On All LED Output
    i2cWriteData(ADDR_PCA9633, PCA9633_MODE2, 0x04); //Set Output in Push-pull Mode
    i2cWriteData(ADDR_PCA9633, PCA9633_PWMOUT, 0xAA); //Set Output in Individual Mode
    setPWM_PCA9633(0, 0x00, 0x00); // Reset All channel to 0;
    setPWM_PCA9633(2, 0x00, 0x00);
}


uint8_t PWM_check(uint8_t pwm){
    if(pwm > 255){
        return 255;
    }
    else if(pwm < 0){
        return 0;
    }
    else{
        return pwm;
    }
}