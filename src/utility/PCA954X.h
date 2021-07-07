#ifndef _PCA954X_H_
#define _PCA954X_H_

#include <Wire.h>
#include <Arduino.h>

#ifndef ADDR_PCA954X
#define ADDR_PCA954X 0x70
#endif

void i2cWriteData(uint8_t dev, uint8_t addr);
void i2cWriteData(uint8_t dev, uint8_t addr, uint8_t data);
void i2cWriteData(uint8_t dev, uint8_t addr, uint8_t data, uint8_t data2);
void i2cWriteBytes(uint8_t dev, uint8_t addr, uint32_t data, uint8_t numBytes);

uint32_t i2cReadData(uint8_t dev, uint8_t numBytes);
uint32_t i2cReadData(uint8_t dev, uint8_t addr, uint8_t numBytes);

void i2cMUXSelect(uint8_t channel, int ver);
void i2cMUXDisable(void);

#endif
