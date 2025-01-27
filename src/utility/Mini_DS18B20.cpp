/**
 * @file Mini_DS18B20.cpp
 * @brief Lightweight library for working with 1-Wire Dallas DS18B20 thermometers.
 *
 * This library provides functions to work with DS18B20 temperature sensors using the 1-Wire protocol.
 * It supports reading the temperature, setting resolution, and handling CRC checks.
 * 
 * Add: Merge into Mini.Dn instance.
 * 
 * @author Egor 'Nich1con' Zakharov & AlexGyver
 * @license MIT
 */
 
#include "Mini_DS18B20.h"

MiniDS18B20::MiniDS18B20(uint8_t pin) : _pin(pin) {}

void MiniDS18B20::begin(uint8_t pin, uint8_t * addr = nullptr, uint8_t numSensors = 1, bool pgm = false) {
    _pin = pin;
    _addr = addr;
    _numSensors = numSensors;
    _pgm = pgm;
    pinMode(_pin, INPUT);
    digitalWrite(_pin, LOW);
}


void MiniDS18B20::setResolution(uint8_t res, uint8_t idx) {
    if (!oneWire_reset(_pin)) return; 
    addressRoutine(idx); 
    oneWire_write(0x4E, _pin); 
    oneWire_write(0xFF, _pin); 
    oneWire_write(0x00, _pin); 
    oneWire_write(((constrain(res, 9, 12) - 9) << 5) | 0x1F, _pin); 
}

void MiniDS18B20::setResolutionAll(uint8_t res) {
    for (int i = 0; i < _numSensors; i++) setResolution(res, i);
}

void MiniDS18B20::setAddress(uint8_t * addr) {
    _addr = addr;
}

bool MiniDS18B20::readAddress(uint8_t * addr) {
    if (!oneWire_reset(_pin)) return 0;
    oneWire_write(0x33, _pin); 
    uint16_t sum = 0; 
    uint8_t crc = 0; 
    for (uint8_t i = 0; i < 8; i++) {
        addr[i] = oneWire_read(_pin);
        sum += addr[i];
        #if(DS_CHECK_CRC == true)
        _ds_crc8_upd(crc, addr[i]);
        #endif
    }
    return !(sum == 0x8F7 || !sum || crc); 
}

void MiniDS18B20::requestTemp(uint8_t idx) {
    state[idx] = 0;
    if (!oneWire_reset(_pin)) return;
    addressRoutine(idx); 
    oneWire_write(0x44, _pin); 
}

void MiniDS18B20::requestTempAll() {
    for (int i = 0; i < _numSensors; i++) requestTemp(i);
}

float MiniDS18B20::getTemp(uint8_t idx) {
    if (!state[idx]) readTemp(idx);
    return (_buf[idx] / 16.0);
}

float MiniDS18B20::requestAndGetTemp(uint8_t idx) {
    requestTemp(idx);
    delay(1);
    if (!state[idx]) readTemp(idx);
    return (_buf[idx] / 16.0);
}

int16_t MiniDS18B20::getTempInt(uint8_t idx) {
    if (!state[idx]) readTemp(idx);
    return (_buf[idx] >> 4);
}

int16_t MiniDS18B20::getRaw(uint8_t idx) {
    if (!state[idx]) readTemp(idx);
    return _buf[idx];
}

bool MiniDS18B20::readTemp(uint8_t idx) {
    state[idx] = 1;
    if (!oneWire_reset(_pin)) return 0;
    addressRoutine(idx); 
    oneWire_write(0xBE, _pin); 
    uint8_t crc = 0; 
    int16_t temp; 
    uint16_t sum = 0;
    for (uint8_t i = 0; i < 9; i++) {
        uint8_t data = oneWire_read(_pin); 
        sum += data;
        #if(DS_CHECK_CRC == true)
        _ds_crc8_upd(crc, data); 
        #endif
        if (i == 0) temp = data;
        else if (i == 1) temp |= (data << 8);
    }
    if (sum == 0x8F7 || !sum || crc) return 0;
    if (temp != 0x0550) _buf[idx] = temp;
    return 1;
}

bool MiniDS18B20::online(uint8_t idx) {
    if (_addr != nullptr) {
        if (!oneWire_reset(_pin)) return 0;
        addressRoutine(idx);
        oneWire_write(0xBE, _pin);
        uint16_t sum = 0;
        for (uint8_t i = 0; i < 5; i++) sum += oneWire_read(_pin);
        return (sum != 0x4FB);
    } else return oneWire_reset(_pin);
}

void MiniDS18B20::addressRoutine(uint8_t idx) {
    if (_addr != nullptr) {
        oneWire_write(0x55, _pin);
        for (uint8_t i = 0; i < 8; i++) {
            if (_pgm) oneWire_write(pgm_read_byte(&_addr[i + idx * 8]), _pin);
            else oneWire_write(_addr[i + idx * 8], _pin);
        }
    } else oneWire_write(0xCC, _pin); 
}

bool MiniDS18B20::oneWire_reset(uint8_t pin) {
    pinMode(pin, OUTPUT);
    delayMicroseconds(600);
    pinMode(pin, INPUT);
    MOW_CLI();
    delayMicroseconds(60);
    bool pulse = digitalRead(pin);
    MOW_SEI();
    delayMicroseconds(600);
    return !pulse;
}

void MiniDS18B20::oneWire_write(uint8_t data, uint8_t pin) {
    for (uint8_t i = 8; i; i--) {
        pinMode(pin, OUTPUT);
        MOW_CLI();
        if (data & 1) {
            delayMicroseconds(5);
            pinMode(pin, INPUT);
            delayMicroseconds(60);
        } else {
            delayMicroseconds(60);
            pinMode(pin, INPUT);
            delayMicroseconds(5);
        }
        MOW_SEI();
        data >>= 1;
    }
}

uint8_t MiniDS18B20::oneWire_read(uint8_t pin) {
    uint8_t data = 0;
    for (uint8_t i = 8; i; i--) {
        data >>= 1;
        MOW_CLI();
        pinMode(pin, OUTPUT);
        delayMicroseconds(2);
        pinMode(pin, INPUT);
        delayMicroseconds(8);
        if (digitalRead(pin)) data |= (1 << 7);
        delayMicroseconds(60);
        MOW_SEI();
    }
    return data;
}

void MiniDS18B20::_ds_crc8_upd(uint8_t & crc, uint8_t data) {
    #if(DS_CRC_USE_TABLE == true)
    crc = pgm_read_byte(&_ds_crc8_table[crc ^ data]);
    #else
    uint8_t i = 8;
    while (i--) {
        crc = ((crc ^ data) & 1) ? (crc >> 1) ^ 0x8C : (crc >> 1);
        data >>= 1;
    }
    #endif
}
