#ifndef _PIXYPIXY_H_
#define _PIXYPIXY_H_

#define MINI_PIXY_I2C_DEFAULT_ADDR                0x54  
#define MINI_PIXY_SYNC_ADDR                       0xae

#define MINI_PIXY_SYNC_BIT                        0xc1

#define MINI_PIXY_REQUEST_BLOCKS                  0x20
#define MINI_PIXY_PAYLOAD_LEN                     0x02

#define MINI_PIXY_ALL_SIG                         0xff // all bits or'ed together
#define MINI_PIXY_MAX_BLOCKS                      0xff // requests all blocks


#include "../../utility/PCA954X.h"

struct ColorBlock
{
    uint16_t signature;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    int16_t angle;
    uint8_t index;
    uint8_t age;
};

class PIXYCam
{
public:
    friend class MiniI2C;
    // void pixyinit();
    void getblock(int n_th=0);
    ColorBlock block;
    ColorBlock emptyblock;

private:
	uint8_t _ch, _ver;
    bool _INIT_FLAG = 0;
    uint8_t _checksum = 0;
    uint8_t _len_of_payload = 0;
    uint8_t *_buf;
    uint8_t mini_pixy_send_buf[5];


    bool isBuffComplete();
    bool isSumCorrect();
    void i2cWriteBuff();
    uint8_t i2cReadbuffer();

    void packblock(uint8_t num_of_block);
};

#endif
