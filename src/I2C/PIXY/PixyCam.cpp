#include "PixyCam.h"

// Get n th biggest color block, captured by PIXY Cam.
void PIXYCam::getblock(int n_th){
  i2cMUXSelect(_ch, _ver);

  // PIXY Cam is not working on MATRIX Mini I2C4
  if (_ch != 3){
    if (_INIT_FLAG == 0){
      // pixy2.init is written by PIXY team,
      // which takes too much time, 
      // so it only needs to execute once.
      pixy2.init();
      _INIT_FLAG = 1;
    }
    
    pixy2.ccc.getBlocks();
    if (pixy2.ccc.numBlocks){ 
      block = pixy2.ccc.blocks[n_th];
    }
    else{
      // If there doesn't exist speicifc color block,
      // then return empty block with sig = 0 .
      block = _EmptyBlock;
    } 
  }
}
