// Made by Alex Tkachenko

#include "MiniHitechColor.h"

	//
	// Constructor
	//
	void MiniHitechColor::begin(){
		DEVICE_ADDRESS = HT_COLOR_DEVADDR;
	}

	//
	// Get Color Value
	//
	byte MiniHitechColor::getColor(){
		return i2cReadData(HT_COLOR_REG_COLOR);
	}

	//
	// Get R Value
	//
	byte MiniHitechColor::getR(){
		return i2cReadData(HT_COLOR_REG_RED);
	}

	//
	// Get G Value
	//
	byte MiniHitechColor::getG(){
		return i2cReadData(HT_COLOR_REG_GREEN);
	}

	//
	// Get B Value
	//
	byte MiniHitechColor::getB(){
		return i2cReadData(HT_COLOR_REG_BLUE);
	}

	//
	// Get RGB Value
	//
	byte* MiniHitechColor::getRGB(){
		i2cReadData(HT_COLOR_REG_RED, 3);
		return dataBuf;
	}

	//
	// Get RGB Value
	//
	void MiniHitechColor::getRGB(byte &r, byte &g, byte &b){
		i2cReadData(HT_COLOR_REG_RED, 3);
		r = dataBuf[0];
		g = dataBuf[1];
		b = dataBuf[2];
		return;
	}

	//
	// Get RGB Value
	//
	byte MiniHitechColor::getGrayscale(){
		getRGB();
		return 0.3*dataBuf[0] + 0.59*dataBuf[1] + 0.11*dataBuf[2];
	}
