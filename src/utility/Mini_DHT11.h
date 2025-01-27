/**
 * @file Mini_DHT11.h
 * @brief Header file for the DHT11 sensor interface library.
 *
 * This file contains the class `MiniDHT11` that handles communication
 * with the DHT11 temperature and humidity sensor.
 * 
 * Add: Merge into Mini.Dn instance.
 *
 * @author Dhruba Saha
 * @version 2.1.0
 * @date 241016 Anthony: Added float temperature return.
 * @license MIT
 */

#ifndef DHT11_H
#define DHT11_H

#include <Arduino.h>

class MXDHT11
{
private:
    int _pin;
    unsigned long _delayMS = 1200;
    static const int ERROR_CHECKSUM = 254;
    static const int ERROR_TIMEOUT = 253;
    static const int TIMEOUT_DURATION = 1000;

    void startSignal();
    int readRawData(byte data[5]);
    byte readByte();

public:
    MXDHT11(int pin = -1);
    void begin(int pin);
    void setDelay(unsigned long delay);
    float readTemperature();
    int readHumidity();
    int readTemperatureHumidity(int &temperature, int &humidity);
    String getErrorString(int errorCode);
};

#endif // DHT11_H
