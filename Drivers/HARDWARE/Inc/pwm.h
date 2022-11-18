/*使用定时器·3 通道1 完全重映像 对应引脚为Pc6*/
#ifndef  _PWM_H
#define  _PWM_H

#include "stm32f10x.h"

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM1_SPWM_Init(u16 arr,u16 psc);

#endif

