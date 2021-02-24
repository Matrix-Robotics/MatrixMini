#include "PixyCam.h"

uint8_t PIXYCam::getBlocks(bool wait=true, uint8_t sigmap=CCC_SIG_ALL, uint8_t maxBlocks=0xff){
  
  // blocks = NULL;
  // numBlocks = 0;
  // uint8_t* m_buf = (uint8_t *)malloc(CAM_BUFFERSIZE);

  // TODO: 
  // uint8_t m_buf[4];

  // m_buf[0] = CCC_SIG_ALL;
  // m_buf[1] = maxBlocks;

  // int m_type = CCC_REQUEST_BLOCKS;
  // int m_length = 2;
  // m_buf[2] = m_type;
  // m_buf[3] = m_length;


  // // i2cWriteBuff(PIXY_I2C_DEFAULT_ADDR, m_buf, m_length+PIXY_SEND_HEADER_SIZE);

  // m_buf[0] = PIXY_NO_CHECKSUM_SYNC&0xff;
  // m_buf[1] = PIXY_NO_CHECKSUM_SYNC>>8;
  // // int m_type = CCC_REQUEST_BLOCKS;
  // // int m_length = 2;
  // // m_buf[2] = m_type;
  // // m_buf[3] = m_length;

  // // // send whole thing -- header and data in one call
  // // return m_link.send(m_buf, m_length+PIXY_SEND_HEADER_SIZE);
  // int len = m_length+PIXY_SEND_HEADER_SIZE;

  
  // // i2cReadBuff(PIXY_I2C_DEFAULT_ADDR, m_buf, 4);

  // m_type = m_buf[0];
  // m_length = m_buf[1];
  
  // uint16_t csSerial = *(uint16_t *)&m_buf[2];
  

  // // i2cReadBuff(CAM_I2C_DEFAULT_ADDR, m_buf, m_length);

  // dataBuf = i2cReadData(PIXY_I2C_DEFAULT_ADDR, 0x02, 4);
  // Serial.println(dataBuf);

}

