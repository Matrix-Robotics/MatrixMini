#include "PixyCam.h"
#include "Wire.h"

void PIXYCam::pixyinit(uint8_t sigmap){
  _sigmap = sigmap;
}

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
          _checksum -= _buf[j + i];
        }
      }
    }
  }

  if (isSumCorrect() && _len_of_payload != 0 && _len_of_payload % 14 == 0){
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

void PIXYCam::pushBlock(){
  _buf = (uint8_t *)malloc(0x104);
  // default MINI_PIXY_MAX_BLOCKS is 8
  blocks = (ColorBlock *)malloc(8 * sizeof(ColorBlock));

  for (int n=1; n<=_count_of_block; n++){
    // n means num_of_block
    blocks[n].signature =  (_buf[n*14+1] << 8 ) + (_buf[n*14]);
    blocks[n].x =  (_buf[n*14+3] << 8 ) + (_buf[n*14+2]);
    blocks[n].y =  (_buf[n*14+5] << 8 ) + (_buf[n*14+4]);
    blocks[n].width =  (_buf[n*14+7] << 8 ) + (_buf[n*14+6]);
    blocks[n].height =  (_buf[n*14+9] << 8 ) + (_buf[n*14+8]);
    blocks[n].angle =  (_buf[n*14+11] << 8 ) + (_buf[n*14+10]);

    blocks[n].index = _buf[n*14+12];
    blocks[n].age = _buf[n*14+13];
  }
}

// Get n largest color block, captured by PIXY Cam.
// 1 is the largest, nth = 2 is a block which smaller then 1, and so on.
bool PIXYCam::getblock(int n_th){
  i2cMUXSelect(_ch, _ver);
  // PIXY Cam is not working on MATRIX Mini I2C4
  if (_ch == 3 or n_th == 0){
    free(_buf);
    return false;
  }
  i2cWriteBuff();
  // count_of_block start counting from 1
  _count_of_block = i2cReadbuffer();
  if (_count_of_block == 0 || n_th > _count_of_block){
    // empty block
    // If there doesn't exist speicifc color block,
    // then return empty block with sig = 0 .
    block = emptyblock;
  }
  else if (_count_of_block == 255)
  {
    // Invalid block
    block = emptyblock;
    free(_buf);
    return false;
  }
  else
  {
    // Valid block
    pushBlock();
    block = blocks[n_th];
  }
  free(_buf);
  return true;
};

int PIXYCam::getCountofBLock(){
  return _count_of_block;
};

int PIXYCam::getX(int sig, int n_th)
{
  uint8_t i = 1;
  while(i <= _count_of_block)
  {
    if (blocks[i].signature == sig)
    {
      return blocks[i].x;
    }
    else
    {
      i++;
    }
  }
};

int PIXYCam::getY(int sig, int n_th)
{
  uint8_t i = 1;
  while(i <= _count_of_block)
  {
    if (blocks[i].signature == sig)
    {
      return blocks[i].y;
    }
    else
    {
      i++;
    }
  }
};

int PIXYCam::getWidth(int sig, int n_th)
{
  uint8_t i = 1;
  while(i <= _count_of_block)
  {
    if (blocks[i].signature == sig)
    {
      return blocks[i].width;
    }
    else
    {
      i++;
    }
  }
};

int PIXYCam::getHeight(int sig, int n_th)
{
  uint8_t i = 1;
  while(i <= _count_of_block)
  {
    if (blocks[i].signature == sig)
    {
      return blocks[i].height;
    }
    else
    {
      i++;
    }
  }
};

int PIXYCam::getArea(int sig, int n_th)
{
  uint8_t i = 1;
  while(i <= _count_of_block)
  {
    if (blocks[i].signature == sig)
    {
      return blocks[i].height * blocks[i].width;
    }
    else
    {
      i++;
    }
  }
};
