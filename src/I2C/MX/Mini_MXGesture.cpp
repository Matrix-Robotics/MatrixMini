/**
 * @file Mini_MXGesture.cpp
 * @brief A library for interfacing with the MATRIX Gesture Seneor PAJ7620 via I2C.
 *
 * This class allows reading 9 gesture from the MATRIX Gesture Seneor.
 *
 * Based On DFRobot_PAJ7620U2 https://github.com/DFRobot/DFRobot_PAJ7620U2
 * Add: Merge into Mini.I2C instance.
 *
 * @author MATRIX Robotics
 * @version 1.0
 * @date 2025
 * @license MIT License
 */
#include "Mini_MXGesture.h"

int MatrixGesture::begin(void) {
    uint16_t partid;
	Wire.begin();
    selectBank(eBank0);
    if (readReg(PAJ7620_ADDR_PART_ID_LOW, &partid, 2) == 0) {
        DBG("bus data access error");
        return ERR_DATA_BUS;
    }
    DBG("part id=0X");
    DBG(partid, HEX);
    if (partid != PAJ7620_PARTID) {
        return ERR_IC_VERSION;
    }
    for (uint16_t i = 0; i < sizeof(initRegisterArray)/sizeof(initRegisterArray[0]); i++) {
		uint8_t reg = pgm_read_byte(&initRegisterArray[i][0]);    // 從 Flash memory 讀取暫存器地址
		uint8_t val = pgm_read_byte(&initRegisterArray[i][1]);    // 從 Flash memory 讀取值
		writeReg(reg, &val, 1);                                  // 傳遞資料到 writeReg
	}
    selectBank(eBank0);
    return ERR_OK;
}

int MatrixGesture::setNormalOrGamingMode(eRateMode_t mode) {
    mode = mode;
    return 0;
}

String MatrixGesture::gestureDescription(int gesture) {
    for (uint16_t i = 0; i < sizeof(gestureDescriptionsTable) /
                                 sizeof(gestureDescriptionsTable[0]);
         i++) {
        // 從 Flash memory 中讀取 gesture 和 description
        int storedGesture = pgm_read_word(&gestureDescriptionsTable[i].gesture);
        const char* description = (const char*)pgm_read_ptr(&gestureDescriptionsTable[i].description);

        if (gesture == storedGesture) {
            return String(description); // 返回描述字串
        }
    }
    return ""; // 如果沒有匹配的手勢，返回空字串
}

void MatrixGesture::setGestureHighRate(bool b) { _gestureHighRate = b; }

int MatrixGesture::getGesture(void) {
    readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_1, &_gesture, 1);
    _gesture = (MatrixGesture::eGesture_t)(((uint16_t)_gesture) << 8);
    if (_gesture == eGestureWave) {
        DBG("Wave1 Event Detected");
        delay(GES_QUIT_TIME);
    } else {
        _gesture = eGestureNone;
        readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_0, &_gesture, 1);  // Read Bank_0_Reg_0x43/0x44 for gesture result.
        _gesture = (MatrixGesture::eGesture_t)(((uint16_t)_gesture) & 0x00ff);
        if (!_gestureHighRate) {
            uint8_t tmp;
            delay(GES_ENTRY_TIME);
            readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_0, &tmp, 1);
            DBG("tmp=0x");
            DBG(tmp, HEX);
            DBG("_gesture=0x");
            DBG(_gesture, HEX);
            _gesture = (MatrixGesture::eGesture_t)(((uint16_t)_gesture) | tmp);
        }
        if (_gesture != eGestureNone) {
            DBG("");
            switch (_gesture) {
                case eGestureRight:
                    DBG("Right Event Detected");
                    break;

                case eGestureLeft:
                    DBG("Left Event Detected");
                    break;

                case eGestureUp:
                    DBG("Up Event Detected");
                    break;

                case eGestureDown:
                    DBG("Down Event Detected");
                    break;

                case eGestureForward:
                    DBG("Forward Event Detected");
                    if (!_gestureHighRate) {
                        delay(GES_QUIT_TIME);
                    } else {
                        delay(GES_QUIT_TIME / 5);
                    }
                    break;

                case eGestureBackward:
                    DBG("Backward Event Detected");
                    if (!_gestureHighRate) {
                        delay(GES_QUIT_TIME);
                    } else {
                        delay(GES_QUIT_TIME / 5);
                    }
                    break;

                case eGestureClockwise:
                    DBG("Clockwise Event Detected");
                    break;

                case eGestureAntiClockwise:
                    DBG("anti-clockwise Event Detected");
                    break;

                default:
                    uint8_t tmp;
                    readReg(PAJ7620_ADDR_GES_PS_DET_FLAG_1, &tmp, 1);
                    if (tmp) {
                        _gesture = eGestureWave;
                        DBG("Wave2 Event Detected");
                    } else {
                        switch (_gesture) {
                            case eGestureWaveSlowlyLeftRight:
                                DBG("LeftRight Wave Event Detected");
                                break;
                            case eGestureWaveSlowlyUpDown:
                                DBG("UpDown Wave Event Detected");
                                break;
                            case eGestureWaveSlowlyForwardBackward:
                                DBG("ForwardBackward Wave Event Detected");
                                break;
                            default:
                                _gesture = eGestureWaveSlowlyDisorder;
                                DBG("Wave Disorder Event Detected");
                                break;
                        }
                    }
                    break;
            }
        }
    }

    // 处理 _gesture 以返回整数
    int gestureResult = 0; // 默认为0，表示没有手势
    switch (_gesture) {
        case eGestureRight:
            gestureResult = 1;
            break;
        case eGestureLeft:
            gestureResult = 2;
            break;
        case eGestureUp:
            gestureResult = 3;
            break;
        case eGestureDown:
            gestureResult = 4;
            break;
        case eGestureForward:
            gestureResult = 5;
            break;
        case eGestureBackward:
            gestureResult = 6;
            break;
        case eGestureClockwise:
            gestureResult = 7;
            break;
        case eGestureAntiClockwise:
            gestureResult = 8;
            break;
        case eGestureWave:
            gestureResult = 9;
            break;
        case eGestureWaveSlowlyLeftRight:
            gestureResult = 10;
            break;
        case eGestureWaveSlowlyUpDown:
            gestureResult = 11;
            break;
        case eGestureWaveSlowlyForwardBackward:
            gestureResult = 12;
            break;
        case eGestureWaveSlowlyDisorder:
            gestureResult = 13;
            break;
        default:
            gestureResult = 0;  // 如果是 eGestureNone 或其他未知手势
            break;
    }

    return gestureResult;  // 返回处理后的整数值
}


int MatrixGesture::selectBank(eBank_t bank) {
    writeReg(PAJ7620_REGITER_BANK_SEL, &bank, 1);
    return 0;
}

void MatrixGesture::writeReg(uint8_t reg, const void *pBuf, size_t size) {
    if (pBuf == NULL) {
        DBG("pBuf is null pointer");
        return;
    }
    uint8_t *_pBuf = (uint8_t *)pBuf;
	i2cMUXSelect();
    Wire.beginTransmission(_deviceAddr);
    Wire.write(&reg, 1);
    for (uint16_t i = 0; i < size; i++) {
        Wire.write(_pBuf[i]);
    }
    Wire.endTransmission();
}

uint8_t MatrixGesture::readReg(uint8_t reg, void *pBuf, size_t size) {
    if (pBuf == NULL) {
        DBG("pBuf is null pointer");
        return 0;
    }
    uint8_t *_pBuf = (uint8_t *)pBuf;
	i2cMUXSelect();
    Wire.beginTransmission(_deviceAddr);
    Wire.write(&reg, 1);
    if (Wire.endTransmission() != 0) {
        DBG("Wire Read Error");
        return 0;
    }
    Wire.requestFrom(_deviceAddr, (uint8_t)size);
    for (uint16_t i = 0; i < size; i++) _pBuf[i] = Wire.read();
    Wire.endTransmission();
    return size;
}

const PROGMEM MatrixGesture::sGestureDescription_t
	MatrixGesture::gestureDescriptionsTable[] = {
		{0, "None"},                  // eGestureNone
		{1, "Right"},                 // eGestureRight
		{2, "Left"},                  // eGestureLeft
		{3, "Up"},                    // eGestureUp
		{4, "Down"},                  // eGestureDown
		{5, "Forward"},               // eGestureForward
		{6, "Backward"},              // eGestureBackward
		{7, "Clockwise"},             // eGestureClockwise
		{8, "Anti-Clockwise"},        // eGestureAntiClockwise
		{9, "Wave"},                  // eGestureWave
		{10, "WaveSlowlyDisorder"},   // eGestureWaveSlowlyDisorder
		{11, "WaveSlowlyLeftRight"},  // eGestureWaveSlowlyLeftRight
		{12, "WaveSlowlyUpDown"},    // eGestureWaveSlowlyUpDown
		{13, "WaveSlowlyForwardBackward"} // eGestureWaveSlowlyForwardBackward
	};


const uint8_t PROGMEM MatrixGesture::initRegisterArray[219][2] = {
    {0xEF, 0x00}, {0x32, 0x29}, {0x33, 0x01}, {0x34, 0x00}, {0x35, 0x01},
    {0x36, 0x00}, {0x37, 0x07}, {0x38, 0x17}, {0x39, 0x06}, {0x3A, 0x12},
    {0x3F, 0x00}, {0x40, 0x02}, {0x41, 0xFF}, {0x42, 0x01}, {0x46, 0x2D},
    {0x47, 0x0F}, {0x48, 0x3C}, {0x49, 0x00}, {0x4A, 0x1E}, {0x4B, 0x00},
    {0x4C, 0x20}, {0x4D, 0x00}, {0x4E, 0x1A}, {0x4F, 0x14}, {0x50, 0x00},
    {0x51, 0x10}, {0x52, 0x00}, {0x5C, 0x02}, {0x5D, 0x00}, {0x5E, 0x10},
    {0x5F, 0x3F}, {0x60, 0x27}, {0x61, 0x28}, {0x62, 0x00}, {0x63, 0x03},
    {0x64, 0xF7}, {0x65, 0x03}, {0x66, 0xD9}, {0x67, 0x03}, {0x68, 0x01},
    {0x69, 0xC8}, {0x6A, 0x40}, {0x6D, 0x04}, {0x6E, 0x00}, {0x6F, 0x00},
    {0x70, 0x80}, {0x71, 0x00}, {0x72, 0x00}, {0x73, 0x00}, {0x74, 0xF0},
    {0x75, 0x00}, {0x80, 0x42}, {0x81, 0x44}, {0x82, 0x04}, {0x83, 0x20},
    {0x84, 0x20}, {0x85, 0x00}, {0x86, 0x10}, {0x87, 0x00}, {0x88, 0x05},
    {0x89, 0x18}, {0x8A, 0x10}, {0x8B, 0x01}, {0x8C, 0x37}, {0x8D, 0x00},
    {0x8E, 0xF0}, {0x8F, 0x81}, {0x90, 0x06}, {0x91, 0x06}, {0x92, 0x1E},
    {0x93, 0x0D}, {0x94, 0x0A}, {0x95, 0x0A}, {0x96, 0x0C}, {0x97, 0x05},
    {0x98, 0x0A}, {0x99, 0x41}, {0x9A, 0x14}, {0x9B, 0x0A}, {0x9C, 0x3F},
    {0x9D, 0x33}, {0x9E, 0xAE}, {0x9F, 0xF9}, {0xA0, 0x48}, {0xA1, 0x13},
    {0xA2, 0x10}, {0xA3, 0x08}, {0xA4, 0x30}, {0xA5, 0x19}, {0xA6, 0x10},
    {0xA7, 0x08}, {0xA8, 0x24}, {0xA9, 0x04}, {0xAA, 0x1E}, {0xAB, 0x1E},
    {0xCC, 0x19}, {0xCD, 0x0B}, {0xCE, 0x13}, {0xCF, 0x64}, {0xD0, 0x21},
    {0xD1, 0x0F}, {0xD2, 0x88}, {0xE0, 0x01}, {0xE1, 0x04}, {0xE2, 0x41},
    {0xE3, 0xD6}, {0xE4, 0x00}, {0xE5, 0x0C}, {0xE6, 0x0A}, {0xE7, 0x00},
    {0xE8, 0x00}, {0xE9, 0x00}, {0xEE, 0x07}, {0xEF, 0x01}, {0x00, 0x1E},
    {0x01, 0x1E}, {0x02, 0x0F}, {0x03, 0x10}, {0x04, 0x02}, {0x05, 0x00},
    {0x06, 0xB0}, {0x07, 0x04}, {0x08, 0x0D}, {0x09, 0x0E}, {0x0A, 0x9C},
    {0x0B, 0x04}, {0x0C, 0x05}, {0x0D, 0x0F}, {0x0E, 0x02}, {0x0F, 0x12},
    {0x10, 0x02}, {0x11, 0x02}, {0x12, 0x00}, {0x13, 0x01}, {0x14, 0x05},
    {0x15, 0x07}, {0x16, 0x05}, {0x17, 0x07}, {0x18, 0x01}, {0x19, 0x04},
    {0x1A, 0x05}, {0x1B, 0x0C}, {0x1C, 0x2A}, {0x1D, 0x01}, {0x1E, 0x00},
    {0x21, 0x00}, {0x22, 0x00}, {0x23, 0x00}, {0x25, 0x01}, {0x26, 0x00},
    {0x27, 0x39}, {0x28, 0x7F}, {0x29, 0x08}, {0x30, 0x03}, {0x31, 0x00},
    {0x32, 0x1A}, {0x33, 0x1A}, {0x34, 0x07}, {0x35, 0x07}, {0x36, 0x01},
    {0x37, 0xFF}, {0x38, 0x36}, {0x39, 0x07}, {0x3A, 0x00}, {0x3E, 0xFF},
    {0x3F, 0x00}, {0x40, 0x77}, {0x41, 0x40}, {0x42, 0x00}, {0x43, 0x30},
    {0x44, 0xA0}, {0x45, 0x5C}, {0x46, 0x00}, {0x47, 0x00}, {0x48, 0x58},
    {0x4A, 0x1E}, {0x4B, 0x1E}, {0x4C, 0x00}, {0x4D, 0x00}, {0x4E, 0xA0},
    {0x4F, 0x80}, {0x50, 0x00}, {0x51, 0x00}, {0x52, 0x00}, {0x53, 0x00},
    {0x54, 0x00}, {0x57, 0x80}, {0x59, 0x10}, {0x5A, 0x08}, {0x5B, 0x94},
    {0x5C, 0xE8}, {0x5D, 0x08}, {0x5E, 0x3D}, {0x5F, 0x99}, {0x60, 0x45},
    {0x61, 0x40}, {0x63, 0x2D}, {0x64, 0x02}, {0x65, 0x96}, {0x66, 0x00},
    {0x67, 0x97}, {0x68, 0x01}, {0x69, 0xCD}, {0x6A, 0x01}, {0x6B, 0xB0},
    {0x6C, 0x04}, {0x6D, 0x2C}, {0x6E, 0x01}, {0x6F, 0x32}, {0x71, 0x00},
    {0x72, 0x01}, {0x73, 0x35}, {0x74, 0x00}, {0x75, 0x33}, {0x76, 0x31},
    {0x77, 0x01}, {0x7C, 0x84}, {0x7D, 0x03}, {0x7E, 0x01}};

void MatrixGesture::i2cMUXSelect(){
	switch (_ver)
	{
	case 2:
		Wire.beginTransmission(ADDR_PCA954X);
		Wire.write(_ch + 4);
		Wire.endTransmission(1);

		delayMicroseconds(300);
		break;
	case 3:
		Wire.beginTransmission(ADDR_PCA954X);
		Wire.write((1 << _ch));
		Wire.endTransmission(1);
		
		delayMicroseconds(300);
		break;
	default:
		break;
	}
}