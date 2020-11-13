#include "ADS1015.h"



/**
 *ReadData From ADS1015
    *Data Format = 3mV/FS
    * @param channel [0-3] choose ADC channel
*/
int adc_read(uint8_t channel){

    i2cWriteData(ADDR_ADS1015, ADS1015_Config, channel, 0x83);
  
    int j = i2cReadData(ADDR_ADS1015, ADS1015_Conversion, 2);
	
    j = j >> 4;

    if (j > 2048) {j -= 4096;}
        
    return map(j, -1667, 1667, -1023, 1023);
}   