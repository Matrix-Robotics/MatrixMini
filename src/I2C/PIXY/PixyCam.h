#ifndef _PIXYCAM_H_
#define _PIXYCAM_H_

#include "../../utility/PCA954X.h"

#define CCC_SIG_ALL                  0xff

#define CAM_I2C_DEFAULT_ADDR 0x54
#define CAM_I2C_MAX_SEND 16 // don't send any more than 16 bytes at a time

#define CAM_TYPE_RESPONSE_ERROR             0x03

#define CAM_RESULT_ERROR                    -1
#define CAM_RESULT_BUSY                     -2
#define CAM_RESULT_PROG_CHANGING            -6

class PIXY{
private:
    uint8_t _ch, _ver;
public:
    friend class MiniI2C;
    uint8_t getBlocks(bool wait=true, uint8_t sigmap=CCC_SIG_ALL, uint8_t maxBlocks=0xff);
    
    
};

#endif
