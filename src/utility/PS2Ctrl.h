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
        uint8_t SWSPI_TXRX(uint8_t command);
        
    public:
        bool L1, R1, L2, R2, L3, R3, SELECT, START;
        bool UP, RIGHT, DOWN, LEFT, TRIANGLE, CIRCLE, X, SQUARE;
        uint8_t RX, RY, LX, LY;
        void polling();
		void init_PS2();
        void begin(uint8_t sck,  uint8_t mosi,  uint8_t miso,  uint8_t css);
};

#endif
