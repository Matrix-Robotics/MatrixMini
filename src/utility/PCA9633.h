#include "PCA954X.h"

#define ADDR_PCA9633  0x62

#define PCA9633_MODE1  0x80
#define PCA9633_MODE2  0x81

#define PCA9633_PWM0  0x82

#define PCA9633_PWMOUT  0x88

void setPWM_PCA9633(uint8_t channel, uint16_t duty);
void init_PCA9633();