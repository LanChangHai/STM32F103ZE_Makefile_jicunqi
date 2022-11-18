#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"
#include "stm32f103_gpio.h"

#define key1 PEin(2)
#define key2 PEin(3)
#define key3 PEin(4)
#define key4 PEin(5)

void key_init(int keys);


#endif

