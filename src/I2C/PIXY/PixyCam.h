#ifndef _PIXYPIXY_H_
#define _PIXYPIXY_H_

#include "../../utility/PCA954X.h"
#include "utility/MiniPixy2I2C.h"

class PIXYCam{
private:
    MiniPixy2I2C minipixy;
	uint8_t _ch, _ver;
    PIXYBlock _EmptyBlock;
    bool _INIT_FLAG = 0;

public:
    friend class MiniI2C;
    PIXYBlock block;
    void getblock(int n_th=0);
};

#endif
