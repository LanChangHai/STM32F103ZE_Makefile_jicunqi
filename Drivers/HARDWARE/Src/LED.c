#include "LED.h"
GPIO_InitTypeDef GPIO_LED;
u16 LED[]={GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15};
void LEDinit(void){
	GPIO_LED.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_LED.GPIO_Speed=GPIO_Speed_50MHz;
}

void openled(u16 GPIO_Pin_x){
 GPIO_LED.GPIO_Pin=GPIO_Pin_x;
 GPIO_ResetBits(GPIOB,GPIO_Pin_x);
}

void closeled(u16 GPIO_Pin_x){
 GPIO_LED.GPIO_Pin=GPIO_Pin_x;
 GPIO_SetBits(GPIOB,GPIO_Pin_x);
}

