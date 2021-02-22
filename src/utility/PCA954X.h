#ifndef _PCA954X_h_
#define _PCA954X_h_

#include <Wire.h>
#include <Arduino.h>


#define ADDR_PCA954X 0x70

void i2cWriteData(byte dev, byte addr);
void i2cWriteData(byte dev, byte addr, uint8_t data);
void i2cWriteData(byte dev, byte addr, uint8_t data, uint8_t data2);

uint32_t i2cReadData(byte dev, int numBytes);
uint32_t i2cReadData(byte dev, byte addr, int numBytes);

void i2cMUXSelect(byte channel, int ver);
void i2cMUXDisable(void);

#endif
