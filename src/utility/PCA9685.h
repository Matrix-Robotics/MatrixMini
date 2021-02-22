#ifndef _PCA9685_h_
#define _PCA9685_h_

#include "PCA954X.h"

#define ADDR_PCA9685  0x60

#define PCA9685_MODE1  0x00
#define PCA9685_MODE2  0x01

#define PCA9685_PWM0_ON_L  0x06
#define PCA9685_PWM_ALLCALL 0xFA

#define PCA9685_PRESCALER 0xFE

void setPWM_PCA9685(uint8_t ch, uint16_t duty);
void setPWM_PCA9685(uint8_t ch, uint16_t duty1, uint16_t duty2);
void setPWM_PCA9685(uint8_t ch, uint16_t duty1, uint16_t duty2, uint16_t duty3);
void init_PCA9685(uint8_t freq);
uint16_t PWM_overflow_check(int pwm);

#endif
