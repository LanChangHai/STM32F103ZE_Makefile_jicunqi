/*ʹ�ö�ʱ����3 ͨ��1 ��ȫ��ӳ�� ��Ӧ����ΪPc6*/
#ifndef  _PWM_H
#define  _PWM_H

#include "stm32f10x.h"

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM1_SPWM_Init(u16 arr,u16 psc);

#endif

