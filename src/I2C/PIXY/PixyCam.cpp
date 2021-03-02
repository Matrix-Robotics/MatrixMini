#include "PixyCam.h"

void PIXYCam::initCam(){
  pixy.init();
}


Block PIXYCam::getBlocks(int n_th=0){
  // grab blocks!
  i2cMUXSelect(_ch, _ver);
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks){ 
    return pixy.ccc.blocks[n_th];
  }
  else{
    return _block;
  }    
}

