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
    bool getblock(int n_th=1);
    void pixyinit(uint8_t sigmap=3);
    int getCountofBLock();
    int getX(int sig=0, int n_th=0);
    int getY(int sig=0, int n_th=0);
    int getWidth(int sig=0, int n_th=0);
    int getHeight(int sig=0, int n_th=0);
    int getArea(int sig=0, int n_th=0);

    ColorBlock block;
    // default MINI_PIXY_MAX_BLOCKS is 8
    ColorBlock *blocks;

private:
    ColorBlock emptyblock;

    uint8_t *_buf;

	uint8_t _ch, _ver;
	uint8_t _sigmap;
    uint8_t _checksum = 0;
    uint8_t _len_of_payload = 0;
    uint8_t _count_of_block = 0;
    uint8_t mini_pixy_send_buf[5];

    bool isSumCorrect();
    bool isBuffComplete();
    bool isPayloadLenCorrect(); 
    void i2cWriteBuff();
    uint8_t i2cReadbuffer();

    void pushBlock();
};

#endif
