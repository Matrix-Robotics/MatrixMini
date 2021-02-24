#ifndef _PIXYPIXY_H_
#define _PIXYPIXY_H_

#include "../../utility/PCA954X.h"

#define CCC_SIG1                     1 
#define CCC_SIG2                     2
#define CCC_SIG3                     4
#define CCC_SIG4                     8
#define CCC_SIG5                     16
#define CCC_SIG6                     32
#define CCC_SIG7                     64
#define CCC_SIG_ALL                  0xff

#define CCC_COLOR_CODES              128

#define CCC_MAX_SIGNATURE                   7
#define CCC_RESPONSE_BLOCKS                 0x21
#define CCC_REQUEST_BLOCKS                  0x20


#define PIXY_TYPE_RESPONSE_ERROR             0x03

#define PIXY_RESULT_ERROR                    -1
#define PIXY_RESULT_BUSY                     -2
#define PIXY_RESULT_PROG_CHANGING            -6
#define PIXY_BUFFERSIZE                      0x104
#define PIXY_NO_CHECKSUM_SYNC                0xc1ae
#define PIXY_I2C_DEFAULT_ADDR                0x54
#define PIXY_I2C_MAX_SEND                    16 // don't send any more than 16 bytes at a time
#define PIXY_SEND_HEADER_SIZE                4

class PIXYCam{
// private:
    //TODO: Use _ch, _ver 
    // uint8_t _ch, _ver;
public:
    friend class MiniI2C;
    uint8_t getBlocks(bool wait=true, uint8_t sigmap=CCC_SIG_ALL, uint8_t maxBlocks=0xff);
};

#endif
