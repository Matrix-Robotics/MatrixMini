#include "PCA9633.h"



    
/**
 *Set PWM to PCA9633
* @param channel [0-3] choose PWM channel;
* @param duty [0-255] pulse of servo; eg: 1, 2, 4
*/
void setPWM_PCA9633(uint8_t channel, uint16_t duty){
    i2cWriteData(ADDR_PCA9633, PCA9633_PWM0 + channel, duty);
}

void init_PCA9633(){
    i2cWriteData(ADDR_PCA9633, PCA9633_MODE1, 0x00); //Turn On All LED Output
    i2cWriteData(ADDR_PCA9633, PCA9633_MODE2, 0x04); //Set Output in Push-pull Mode
    i2cWriteData(ADDR_PCA9633, PCA9633_PWMOUT, 0xAA); //Set Output in Individual Mode
    i2cWriteData(ADDR_PCA9633, PCA9633_PWM0, 0x0000); // Reset All channel to 0;
}