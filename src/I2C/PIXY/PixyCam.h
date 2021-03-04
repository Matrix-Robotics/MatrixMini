#ifndef _PIXYPIXY_H_
#define _PIXYPIXY_H_

#include "../../utility/PCA954X.h"
#include "utility/Pixy2I2C.h"

class PIXYCam{
private:
    Pixy2I2C pixy;
	uint8_t _ch, _ver;
    bool _INIT_FLAG = 0;

public:
    friend class MiniI2C;
    Block block;
    void getblock(int n_th);
};

#endif
