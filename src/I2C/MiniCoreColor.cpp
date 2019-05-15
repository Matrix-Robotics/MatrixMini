#include "MiniCoreColor.h"

	//
	// Constructor
	//
	void MiniCoreColor::begin(){
		DEVICE_ADDRESS = CORE_COLOR_DEVADDR;
	}

	void MiniCoreColor::begin(int address){
		DEVICE_ADDRESS = address;
	}

	//
	// Get Color Value in default active mode
	//
	byte MiniCoreColor::getColor(){
		return i2cReadData(CORE_COLOR_REG_COLOR);
	}

	//
	// Get R Value
	//
	byte MiniCoreColor::getR(){
		return i2cReadData(CORE_COLOR_REG_RED);
	}

	//
	// Get G Value
	//
	byte MiniCoreColor::getG(){
		return i2cReadData(CORE_COLOR_REG_GREEN);
	}

	//
	// Get B Value
	//
	byte MiniCoreColor::getB(){
		return i2cReadData(CORE_COLOR_REG_BLUE);
	}

	//
	// Get RGB Value
	//
	byte* MiniCoreColor::getRGB(){
		i2cReadData(CORE_COLOR_REG_RED, 3);
		return dataBuf;
	}

	//
	// Get RGB Value
	//
	void MiniCoreColor::getRGB(byte &r, byte &g, byte &b){
		i2cReadData(CORE_COLOR_REG_RED, 3);
		r = dataBuf[0];
		g = dataBuf[1];
		b = dataBuf[2];
		return;
	}

	//
	// Get RGB Value
	//
	byte MiniCoreColor::getGrayscale(){
		getRGB();
		return 0.3*dataBuf[0] + 0.59*dataBuf[1] + 0.11*dataBuf[2];
	}

	//
	//Set Modes: Active/ PASSIVE at 60Hz
	//
	void MiniCoreColor::setActiveMode(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COLOR_CMD_ACTIVE);
		i2cWriteData(CORE_REG_COMMAND,CORE_COLOR_CMD_60HZ);
	}

	void MiniCoreColor::setPassiveMode(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COLOR_CMD_PASSIVE);
		i2cWriteData(CORE_REG_COMMAND,CORE_COLOR_CMD_60HZ);
	}
	//
	//Calibrations
	//
	void MiniCoreColor::setWhiteBalance(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COLOR_CMD_WB_CAL);
		while(1){
			if(i2cReadData(CORE_REG_COMMAND) !=CORE_COLOR_CMD_WB_CAL) break;
		}
	}

	void MiniCoreColor::setBlackLevel(){
		i2cWriteData(CORE_REG_COMMAND,CORE_COLOR_CMD_BL_CAL);
		while(1){
			if(i2cReadData(CORE_REG_COMMAND) !=CORE_COLOR_CMD_BL_CAL) break;
		}
	}
