#include "WS2812b.h"

uint32_t RRGB1 = 0x000000;
uint32_t RRGB2 = 0x000000;

void set_RGB1(uint32_t A){
    RRGB1 = A;
}

void set_RGB2(uint32_t B){
    RRGB2 = B;
}


void send_1(){
    PORTB |= (1<<0);
    _delay_us(0.8);

    PORTB &= (0<<0);
}

void send_0(){
    PORTB |= (1<<0);
    _delay_us(0.2);

    PORTB &= (0<<0);
    _delay_us(0.1);
}

void send_buff(int pin){
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    delay(1);

    for(int i = 24; i > 0; i--) {
        if(getBits(RRGB1, i)){
        send_1();
        }
        else{
        send_0();
        }
    }

    for(int i = 24; i > 0; i--) {
        if(getBits(RRGB2, i)){
        send_1();
        }
        else{
        send_0();
        }
    }

    digitalWrite(pin, LOW);

    delay(10);
}

int getBits(uint64_t x, int p)
{
  return ( x >> (p-1) ) & ~( ~0 << 1 );
}