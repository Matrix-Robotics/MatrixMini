#ifndef _PCA9633_H_
#define _PCA9633_H_

#include "PCA954X.h"

#define ADDR_PCA9633  0x62

#define PCA9633_MODE1  0x80
#define PCA9633_MODE2  0x81

#define PCA9633_PWM0  0x82

#define PCA9633_PWMOUT  0x88

void init_PCA9633();

void setPWM_PCA9633(uint8_t channel, uint8_t duty);
void setPWM_PCA9633(uint8_t channel, uint8_t duty1, uint8_t duty2);

uint8_t PWM_check(uint8_t pwm);

#endif
