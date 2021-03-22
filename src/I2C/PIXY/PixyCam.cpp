#include "PixyCam.h"

void PIXYCam::getblock(int n_th){
  i2cMUXSelect(_ch, _ver);

  // PIXY Cam is not working on MATRIX Mini I2C4
  if (_ch != 3){
    if (_INIT_FLAG == 0){
      pixy.init();
      _INIT_FLAG = 1;
    }
    
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks){ 
      block = pixy.ccc.blocks[n_th];
    }
    else{
      block = _EmptyBlock;
    } 
  }
}
