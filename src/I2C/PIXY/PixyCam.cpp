#include "PixyCam.h"

#define CCC_SIG1                     1 
#define CCC_SIG2                     2
#define CCC_SIG3                     4
#define CCC_SIG4                     8
#define CCC_SIG5                     16
#define CCC_SIG6                     32
#define CCC_SIG7                     64
#define CCC_COLOR_CODES              128

#define CCC_MAX_SIGNATURE                   7
#define CCC_RESPONSE_BLOCKS                 0x21
#define CCC_REQUEST_BLOCKS                  0x20

#define CAM_BUFFERSIZE                      0x104


uint8_t PIXY::getBlocks(bool wait=true, uint8_t sigmap=CCC_SIG_ALL, uint8_t maxBlocks=0xff){
  // blocks = NULL;
  // numBlocks = 0;
  uint8_t* m_buf = (uint8_t *)malloc(CAM_BUFFERSIZE);

  // TODO: 
  i2cWriteData(CAM_I2C_DEFAULT_ADDR, 0xc1ae);

  Serial.print("Read:");
  Serial.println(i2cReadData(CAM_I2C_DEFAULT_ADDR, 4));

  //   // If we're waiting for frame data, don't thrash Pixy with requests.
  //   // We can give up half a millisecond of latency (worst case)	
  //   delayMicroseconds(500);
  // }
}

