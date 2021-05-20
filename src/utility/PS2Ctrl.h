#ifndef _PS2Ctrl_H_
#define _PS2Ctrl_H_

#include <Arduino.h>

class PS2Ctrl{
    private:
        uint8_t _rx[6];
        uint8_t _sck_mask, _mosi_mask, _miso_mask, _css_mask;
        volatile uint8_t *_sck_port, *_mosi_port, *_miso_port, *_css_port;
        void SWSPI_BEGIN();
        void SWSPI_END();
        bool init_PS2();
        uint8_t SWSPI_TXRX(uint8_t command);
        uint8_t _ver = 1;
        friend class MatrixMini_;
        
    public:
        bool L1, R1, L2, R2, L3, R3, SELECT, START;
        bool UP, RIGHT, DOWN, LEFT, TRIANGLE, CIRCLE, CROSS, SQUARE;
        uint8_t RX, RY, LX, LY;
        void polling();
        bool begin();
};

#endif
