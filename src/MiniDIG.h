#ifndef _MINIDIG_H_
#define _MINIDIG_H_

#include <Arduino.h>
#include "utility/HC04.h"
#include "utility/Mini_DHT11.h"
#include "utility/Mini_DS18B20.h"
#include <SoftwareSerial.h>
class MiniDIG
{
private:
	int _pin1;
	int _pin2;
	void begin(int, int);
	bool _flag = true;
public:
	MiniUS US;
	MXDHT11 MXDHT;
	MiniDS18B20 MXOnewireDT;
	
	bool get();
	void set(byte);
	SoftwareSerial Serial = SoftwareSerial(1,1);
	friend class MatrixMini_;
};

#endif
