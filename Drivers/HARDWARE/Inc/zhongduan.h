#ifndef _zhongduan_h
#define _zhongduan_h

#include <stm32f10x.h>

void NVIC_fenzu(u8 fenzu);
void NVIC_Init(u8 qiangduan,u8 xiangying,u8 zhongduanhao,u8 fenzu);
void Exti_NVIC_peizhi(u32 GPIOx,u8 Bitx,u8 chufamoshi);

#endif

