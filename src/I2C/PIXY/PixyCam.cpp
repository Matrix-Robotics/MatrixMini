#include "PixyCam.h"
#include "Wire.h"

bool PIXYCam::isBuffComplete(){
  Wire.requestFrom((uint8_t)MINI_PIXY_I2C_DEFAULT_ADDR, (uint8_t)2);
  // 16-bit sync
  while (Wire.available())
  {
    if (Wire.read() == 175 && Wire.read() == 193)
    {
      return true;
    }
  }
  return false;
}

bool PIXYCam::isSumCorrect(){
  if (_checksum == 0){
    return true;
  }
  return false;
}

void PIXYCam::i2cWriteBuff(){
  mini_pixy_send_buf[0] = MINI_PIXY_SYNC_BIT;
  mini_pixy_send_buf[1] = MINI_PIXY_REQUEST_BLOCKS;
  mini_pixy_send_buf[2] = MINI_PIXY_PAYLOAD_LEN;
  mini_pixy_send_buf[3] = MINI_PIXY_ALL_SIG;
  mini_pixy_send_buf[4] = MINI_PIXY_MAX_BLOCKS;

  Wire.beginTransmission(MINI_PIXY_I2C_DEFAULT_ADDR);

  Wire.write(MINI_PIXY_SYNC_ADDR);
  Wire.write(mini_pixy_send_buf, 5);

  Wire.endTransmission(1);
}

uint8_t PIXYCam::i2cReadbuffer(){
  uint8_t n = 0;
  _buf = (uint8_t *)malloc(0x104);
  
  if (isBuffComplete())
  {
    Wire.requestFrom((uint8_t)MINI_PIXY_I2C_DEFAULT_ADDR, (uint8_t)(4));
    if (Wire.available())
    {
      Wire.read();
      // Length of payload
      _len_of_payload = Wire.read();

      // 16-bit checksum
      uint8_t _low_bit = Wire.read();
      uint8_t _high_bit = Wire.read();
      _checksum = (_high_bit << 8 ) | (_low_bit & 0xff);

      for (uint8_t i = 0; i < _len_of_payload; i += n)
      {
        // requestFrom len_of_payload at once doesn't work.
        n = Wire.requestFrom((uint8_t)MINI_PIXY_I2C_DEFAULT_ADDR, (uint8_t)(_len_of_payload - i));
        for (uint8_t j = 0; j < n; j++)
        {
          _buf[j + i] = Wire.read();
          Serial.print("r ");
          Serial.print(j + i);
          Serial.print(" ");
          Serial.println(_buf[j + i]);
          _checksum -= _buf[j + i];
        }
      }
    };
  }
  Serial.print("end checkusum ");
  Serial.println(_checksum);

  if (isSumCorrect() && _len_of_payload != 0){
    // Valid block
    return _len_of_payload / 14;
  }
  else if(_len_of_payload != 0)
  {
    // broken buf -> Invalid block
    return 255;
  }
  
  // empty buf -> empty block
  return 0;
}

void PIXYCam::packblock(uint8_t n){
  block.signature =  (_buf[n*14+1] << 8 ) | (_buf[n*14] & 0xff);
  block.x =  (_buf[n*14+3] << 8 ) | (_buf[n*14+2] & 0xff);
  block.y =  (_buf[n*14+5] << 8 ) | (_buf[n*14+4] & 0xff);
  block.width =  (_buf[n*14+7] << 8 ) | (_buf[n*14+6] & 0xff);
  block.height =  (_buf[n*14+9] << 8 ) | (_buf[n*14+8] & 0xff);
  block.angle =  (_buf[n*14+11] << 8 ) | (_buf[n*14+10] & 0xff);
  block.index = _buf[n*14+12];
  block.age = _buf[n*14+13];
}

// Get n largest color block, captured by PIXY Cam.
void PIXYCam::getblock(int n_th){
  i2cWriteBuff();
  uint8_t count_of_block = i2cReadbuffer();
  Serial.print("count_of_block ");
  Serial.println(count_of_block);

  //TODO no block handle
  // packblock(count_of_block);
  free(_buf);
};


// void PIXYCam::getblock(int n_th){
  // i2cMUXSelect(_ch, _ver);

  // // PIXY Cam is not working on MATRIX Mini I2C4
  // if (_ch != 3){
  //   if (_INIT_FLAG == 0){
  //     // minipixy.init is written by PIXY team,
  //     // which takes too much time, 
  //     // so it only needs to execute once.
  //     minipixy.pixyinit();

  //     _INIT_FLAG = 1;
  //   }
    
  //   minipixy.pixyccc.getBlocks();
  //   if (minipixy.pixyccc.numBlocks){ 
  //     block = minipixy.pixyccc.blocks[n_th];
  //   }
  //   else{
  //     // If there doesn't exist speicifc color block,
  //     // then return empty block with sig = 0 .
  //     block = _EmptyBlock;
  //   } 
  // }
// }
