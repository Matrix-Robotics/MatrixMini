#include "PCA954X.h"

#define ADDR_ADS1015  0x48

#define ADS1015_Conversion 0x00
#define ADS1015_Config 0x01

#define ADS1015_AIN0  0x40
#define ADS1015_AIN1  0x50
#define ADS1015_AIN2  0x60
#define ADS1015_AIN3  0x70

#define ADS1015_GAIN_05  0x06
#define ADS1015_GAIN_1  0x04
#define ADS1015_GAIN_2  0x02
#define ADS1015_GAIN_3  0x00

int adc_read(uint8_t channel);