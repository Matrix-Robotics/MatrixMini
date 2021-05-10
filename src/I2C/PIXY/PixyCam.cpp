#include "PixyCam.h"
#include "Wire.h"

void PIXYCam::pixyinit(uint8_t sigmap)
{
  _sigmap = sigmap;
  i2cWriteBuff();
}

bool PIXYCam::isBuffComplete(){
  Wire.requestFrom((uint8_t)MINI_PIXY_I2C_DEFAULT_ADDR, (uint8_t)3);
  while (Wire.available())
  {
    // 16-bit sync
    if (Wire.read() == 175 && Wire.read() == 193 && Wire.read() ==33)
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
  _send_buf[0] = MINI_PIXY_SYNC_BIT;
  _send_buf[1] = MINI_PIXY_REQUEST_BLOCKS;
  _send_buf[2] = MINI_PIXY_PAYLOAD_LEN;
  _send_buf[3] = MINI_PIXY_ALL_SIG;
  _send_buf[4] = MINI_PIXY_MAX_BLOCKS;

  Wire.beginTransmission(MINI_PIXY_I2C_DEFAULT_ADDR);

  Wire.write(MINI_PIXY_SYNC_ADDR);
  Wire.write(_send_buf, 5);

  Wire.endTransmission(1);
}

uint8_t PIXYCam::i2cReadbuffer()
{
  uint8_t n = 0;
  _recv_buf = (uint8_t *)malloc(0x104);

  if (isBuffComplete())
  {
    Wire.requestFrom((uint8_t)MINI_PIXY_I2C_DEFAULT_ADDR, (uint8_t)(3));
    if (Wire.available())
    {
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
          _recv_buf[j + i] = Wire.read();
          _checksum -= _recv_buf[j + i];
        }
      }
    }
  }

  if (isSumCorrect() && _len_of_payload != 0 && _len_of_payload % 14 == 0)
  {
    // Valid block
    return _len_of_payload / 14;
  }
  else if (_len_of_payload != 0)
  {
    // broken buf -> Invalid block
    return 255;
  }
  // empty buf -> empty block
  return 0;
}

ColorBlock PIXYCam::selectBlock(int sig, int n_th){
  for (n_th; n_th <= _count_of_block; n_th ++)
  {
    int n = n_th-1;
    _block.signature =  (_recv_buf[n*14+1] << 8 ) | (_recv_buf[n*14] & 0xff);
    if (sig == 0 || sig == (int)(_block.signature))
    {
      _block.x =  (_recv_buf[n*14+3] << 8 ) | (_recv_buf[n*14+2] & 0xff);
      _block.y =  (_recv_buf[n*14+5] << 8 ) | (_recv_buf[n*14+4] & 0xff);
      _block.width =  (_recv_buf[n*14+7] << 8 ) | (_recv_buf[n*14+6] & 0xff);
      _block.height =  (_recv_buf[n*14+9] << 8 ) | (_recv_buf[n*14+8] & 0xff);
      _block.angle =  (_recv_buf[n*14+11] << 8 ) | (_recv_buf[n*14+10] & 0xff);
      _block.index = _recv_buf[n*14+12];
      _block.age = _recv_buf[n*14+13];
      return _block;
    }
  }
  _block = emptyblock;
  return _block;
}

// Get n largest color block, captured by PIXY Cam.
// 1 is the largest, nth = 2 is a block which smaller then 1, and so on.
bool PIXYCam::getblock(int sig, int n_th){
  i2cMUXSelect(_ch, _ver);
  if (n_th == 0){
    n_th ++;
  }
  i2cWriteBuff();
  // count_of_block start counting from 1
  _count_of_block = i2cReadbuffer();

  //     Empty block      
  if (_count_of_block == 0)
  {
    // Empty block has sig = 0 .
    block = emptyblock;
    free(_recv_buf);
    return true;
  }
  //       Invalid block           | n_th is out of range
  else if (_count_of_block == 255 || n_th > _count_of_block)
  {
    block = emptyblock;
    free(_recv_buf);
    return false;
  }
  
  // sig=0, n_th=1 means select the largest block with no specific signature.
  block = selectBlock(sig, n_th);
  free(_recv_buf);
  return true;
};

int PIXYCam::getCountofBlock()
{
  return _count_of_block;
};
