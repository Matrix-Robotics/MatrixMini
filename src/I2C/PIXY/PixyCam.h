#ifndef _PIXYPIXY_H_
#define _PIXYPIXY_H_

#define MINI_PIXY_I2C_DEFAULT_ADDR                0x54  
#define MINI_PIXY_SYNC_ADDR                       0xae

#define MINI_PIXY_SYNC_BIT                        0xc1

#define MINI_PIXY_REQUEST_BLOCKS                  0x20
#define MINI_PIXY_PAYLOAD_LEN                     0x02

#define MINI_PIXY_ALL_SIG                         0xff // all bits or'ed together
#define MINI_PIXY_MAX_BLOCKS                      0x08 // Maximum blocks to return, 0~255, default: 8


#include "../../utility/PCA954X.h"

typedef struct __ColorBlock
{
    uint16_t signature;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    int16_t angle;
    uint8_t index;
    uint8_t age;
} ColorBlock;

class PIXYCam
{
public:
    friend class MiniI2C;
    bool getblock(int sig=0, int n_th=1);
    void pixyinit(uint8_t sigmap=3);
    int getCountofBlock();

    ColorBlock block;
    ColorBlock emptyblock;

private:
    uint8_t *_recv_buf;

	uint8_t _ch, _ver;
	uint8_t _sigmap;
    uint8_t _checksum = 0;
    uint8_t _len_of_payload = 0;
    uint8_t _count_of_block = 0;
    uint8_t _send_buf[5];

    ColorBlock _block;

    bool isSumCorrect();
    bool isBuffComplete();
    void i2cWriteBuff();
    uint8_t i2cReadbuffer();

    ColorBlock selectBlock(int sig=0, int n_th=1);
};

#endif
