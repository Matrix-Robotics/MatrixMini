#ifndef _PIXYPIXY_H_
#define _PIXYPIXY_H_

#include "../../utility/PCA954X.h"
#include "utility/Pixy2I2C.h"

#define SIGG 1
class PIXYCam{
private:
    Pixy2I2C pixy;
	uint8_t _ch, _ver;
    Block _block;
public:
    friend class MiniI2C;
    void initCam();
    Block getBlocks(int n_th);
};

#endif
