/**
 * @file Mini_DHT11.cpp
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

#include "Mini_DHT11.h"

MXDHT11::MXDHT11(int pin) : _pin(pin) {}

void MXDHT11::begin(int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

void MXDHT11::setDelay(unsigned long delay)
{
    _delayMS = delay;
}

void MXDHT11::startSignal()
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(20);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(45);
    pinMode(_pin, INPUT);
}

int MXDHT11::readRawData(byte data[5])
{
    delay(_delayMS);
    startSignal();
    unsigned long timeout_start = millis();

    while (digitalRead(_pin) == HIGH)
    {
        if (millis() - timeout_start > TIMEOUT_DURATION)
        {
            return ERROR_TIMEOUT;
        }
    }

    delayMicroseconds(80);
    if (digitalRead(_pin) == HIGH)
    {
        delayMicroseconds(80);
        for (int i = 0; i < 5; i++)
        {
            data[i] = readByte();
        }

        if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
        {
            return 0; // Success
        }
        else
        {
            return ERROR_CHECKSUM;
        }
    }
    return ERROR_TIMEOUT;
}

byte MXDHT11::readByte()
{
    byte value = 0;
    for (int i = 0; i < 8; i++)
    {
        while (digitalRead(_pin) == LOW)
            ;
        delayMicroseconds(30);
        if (digitalRead(_pin) == HIGH)
        {
            value |= (1 << (7 - i));
        }
        while (digitalRead(_pin) == HIGH)
            ;
    }
    return value;
}

float MXDHT11::readTemperature()
{
    byte data[5];
    int error = readRawData(data);
    if (error != 0)
    {
        return error;
    }

    float t = (float)data[3] / 10;
    return data[2] + t;
}

int MXDHT11::readHumidity()
{
    byte data[5];
    int error = readRawData(data);
    if (error != 0)
    {
        return error;
    }

    return data[0];
}

int MXDHT11::readTemperatureHumidity(int &temperature, int &humidity)
{
    byte data[5];
    int error = readRawData(data);
    if (error != 0)
    {
        return error;
    }

    humidity = data[0];
    float t = (float)data[3] / 10;
    temperature = data[2] + t;
    return 0;
}

String MXDHT11::getErrorString(int errorCode)
{
    switch (errorCode)
    {
    case ERROR_TIMEOUT:
        return "Error 253: Timeout reading from DHT11.";
    case ERROR_CHECKSUM:
        return "Error 254: Checksum mismatch reading from DHT11.";
    default:
        return "Error: Unknown.";
    }
}
