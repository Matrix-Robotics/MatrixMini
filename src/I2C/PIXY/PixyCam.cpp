#include "PixyCam.h"

// Get n largest color block, captured by PIXY Cam.
void PIXYCam::getblock(int n_th){
  i2cMUXSelect(_ch, _ver);

  // PIXY Cam is not working on MATRIX Mini I2C4
  if (_ch != 3){
    if (_INIT_FLAG == 0){
      // minipixy.init is written by PIXY team,
      // which takes too much time, 
      // so it only needs to execute once.
      minipixy.pixyinit();
      _INIT_FLAG = 1;
    }
    
    minipixy.ccc.getBlocks();
    if (minipixy.ccc.numBlocks){ 
      block = minipixy.ccc.blocks[n_th];
    }
    else{
      // If there doesn't exist speicifc color block,
      // then return empty block with sig = 0 .
      block = _EmptyBlock;
    } 
  }
}
