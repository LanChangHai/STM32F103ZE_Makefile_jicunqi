#ifndef __usart_H
#define __usart_H

#include "stdio.h"
#include "stm32f10x.h"
#include "zhongduan.h"
#include "string.h"

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

extern u8  USART1_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         		//接收状态标记
extern u8  USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         		//接收状态标记
extern u8  USART3_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记

void usart3_init(u32 pclk1,u32 bound);
void usart2_init(u32 pclk1,u32 bound);
//如果想串口中断接收，请不要注释以下宏定义
void usart1_init(u32 pclk2,u32 bound);

void Send_char(USART_TypeDef *Usart,char c); //发送一个字符
void Send_string(USART_TypeDef *Usart,char string[]); //发送一个字符串

#endif 

