#ifndef _DMA_H
#define _DMA_H

#include "stm32f10x.h"
#include "delay.h"

void DMA1_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//≈‰÷√DMA1_CHx
void DMA1_Enable(DMA_Channel_TypeDef*DMA_CHx);// πƒ‹DMA1_CHx		 

#endif

