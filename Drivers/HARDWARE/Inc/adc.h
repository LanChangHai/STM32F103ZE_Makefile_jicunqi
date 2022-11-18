#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"
#include "delay.h"

//extern u16 dianya[10];

void adc_init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch);

#endif 

