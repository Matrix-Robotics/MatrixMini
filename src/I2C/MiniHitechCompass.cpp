// #include "MiniHitechCompass.h"

// 	//
// 	// Constructor
// 	//
// 	MiniHitechCompass::MiniHitechCompass(byte chan){
// 		_chan = chan;
// 	}

// 	void MiniHitechCompass::begin(){
// 		DEVICE_ADDRESS = HT_COMPASS_DEVADDR;
// 		i2cMUXSelect(_chan);
// 	}

// 	void MiniHitechCompass::startCalibration(){
// 		i2cMUXSelect(_chan);
// 		i2cWriteData(HT_COMPASS_REG_COMMAND, 0x43);
// 		return;
// 	}

// 	bool MiniHitechCompass::finishCalibration(){
// 		i2cMUXSelect(_chan);
// 		i2cWriteData(HT_COMPASS_REG_COMMAND, 0);
// 		delay(50);
// 		i2cReadData(HT_COMPASS_REG_COMMAND);
// 		if (dataBuf[0]==0) return true;
// 		else return false;
// 	}

// 	//
// 	// Get Two Degree Heading
// 	//
// 	byte MiniHitechCompass::getRawHeading2(){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(HT_COMPASS_HEADING2);
// 		return dataBuf[0];
// 	}

// 	//
// 	// Get One Degree Adder
// 	//
// 	int MiniHitechCompass::getRawHeading1(){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(HT_COMPASS_HEADING1);
// 		return dataBuf[0];
// 	}

// 	//
// 	// Get Raw Heading
// 	//
// 	int MiniHitechCompass::getRawHeading(){
// 		i2cMUXSelect(_chan);
// 		i2cReadData(HT_COMPASS_HEADING, 2);
// 		return (((int)dataBuf[0]) << 8) + dataBuf[1];
// 	}

// 	//
// 	// Get Computed Heading
// 	//
// 	int MiniHitechCompass::getHeading(){
// 		i2cMUXSelect(_chan);
// 		return getRawHeading2()*2+getRawHeading1();
// 	}
