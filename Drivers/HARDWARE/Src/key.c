#include "key.h"

void key_init(int keys)
{
	RCC->APB2ENR|=1<<6;
	switch(keys){
		case 1: GPIOE->CRL&=0xffff0ff; GPIOE->CRL|=(0x8)<<8; GPIOE->ODR|=1<<2; break;
	    case 2: GPIOE->CRL&=0xfff0fff; GPIOE->CRL|=(0x8)<<12; GPIOE->ODR|=1<<3; break;
		case 3: GPIOE->CRL&=0xff0ffff; GPIOE->CRL|=(0x8)<<16; GPIOE->ODR|=1<<4; break;
		case 4: GPIOE->CRL&=0xf0fffff; GPIOE->CRL|=(0x8)<<20; GPIOE->ODR|=1<<5; break;
		default: break;
	}
}




