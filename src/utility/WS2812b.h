#ifndef _WS2812b_h_
#define _WS2812b_h_

#include <Arduino.h>

void set_RGB1(uint32_t A);
void set_RGB2(uint32_t A);
void set_det_led(uint32_t C);

void send_1();
void send_0();

int getBits(uint64_t x, int p);

void send_buff(int pin);

#endif