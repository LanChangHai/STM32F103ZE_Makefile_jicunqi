#ifndef _LED_H
#define _LED_H

#include "stm32f10X.h"
#include "stm32f103_gpio.h"

void LEDinit(void);
void openled(u16 GPIO_Pin_x);
void closeled(u16 GPIO_Pin_x);

extern u16 LED[];

#endif

