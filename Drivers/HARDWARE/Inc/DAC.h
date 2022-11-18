#ifndef __DAC_H
#define __DAC_H

#include "stm32f10x.h"
#include "stm32f103_gpio.h"

void stm32HD_DACinit(void);
void Dac1_Set_Vol(u16 vol);

#endif

