#ifndef _Delay_h
#define _Delay_h

#include "stm32f10x.h"

void delay_init(u8 SYSCLK);
void delay_us(u16 us);
void delay_ms(u16 ms);

#endif

